
// Game
#include "Cpp_InventorySystemCharacter.h"
#include "TimerManager.h"
#include "UI/Cpp_InventoryHUD.h"
#include "Components/Cpp_AC_Inventory.h"
#include "World/Pickup.h"
#include "ItemBase.h"

// Engine
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "InputActionValue.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACpp_InventorySystemCharacter

ACpp_InventorySystemCharacter::ACpp_InventorySystemCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	PlayerInventory = CreateDefaultSubobject<UCpp_AC_Inventory>(TEXT("PlayerInventory"));
	PlayerInventory->SetSlotsCapacity(20);
	PlayerInventory->SetWeightCapacity(50.0f);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AimingCameraTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AimingCameraTimeline"));
	DefaultCameraLocation = FVector{0.0f, 0.0f, 65.0f};
	AimingCameraLocation = FVector{175.0f, 50.0f, 55.0f};

	InteractionFrequency = 0.1f;
	InteractionCheckDistance = 225.0f;

	BaseEyeHeight = 74.0f;
}

void ACpp_InventorySystemCharacter::BeginPlay() {
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	HUD = Cast<ACpp_InventoryHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}
void ACpp_InventorySystemCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionFrequency) {
		PerformInteractionCheck();
	}
}

void ACpp_InventorySystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACpp_InventorySystemCharacter::BeginInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ACpp_InventorySystemCharacter::EndInteract);
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACpp_InventorySystemCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACpp_InventorySystemCharacter::Look);

		// Toggle Menu
		EnhancedInputComponent->BindAction(ToggleMenuAction, ETriggerEvent::Started, this, &ACpp_InventorySystemCharacter::ToggleMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ACpp_InventorySystemCharacter::UpdateInteractionWidget() const {
	if(IsValid(TargetInteractable.GetObject())) {
		HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}
void ACpp_InventorySystemCharacter::DropItem(UItemBase* ItemToDrop, int32 QuantityToDrop) {
	if (PlayerInventory->FindMatchingItem(ItemToDrop)) {
		FActorSpawnParameters SpawnParams; // Struct that defines how the actor should be spawned
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true; // always spawn the actor
		// Adjust the spawn location to avoid collision but always spawn the actor
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; 
		
		const FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
		const FTransform SpawnTransform = FTransform(GetActorRotation(), SpawnLocation);

		const int32 RemovedQuantity = PlayerInventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		APickup* Pickup = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);
		Pickup->InitializeDrop(ItemToDrop, RemovedQuantity);
	}
	else {
		UE_LOG(LogTemplateCharacter, Warning, TEXT("Item not found in inventory somehow!"));
	}
}

void ACpp_InventorySystemCharacter::PerformInteractionCheck() {
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();

	FVector TraceStart{GetPawnViewLocation()};
	FVector TraceEnd{TraceStart + GetViewRotation().Vector() * InteractionCheckDistance};

	float lookDirection{(float)FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector())};

	if(lookDirection > 0) {
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);
		FHitResult TraceHit;

		if(GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams)) {
			// Check if the actor implements the Interaction Interface
			if(TraceHit.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass())) {
				// Check if the actor is within interaction distance & is not the current interactable
				if(TraceHit.GetActor() != InteractionData.CurrentInteractable) {
					FoundInteractable(TraceHit.GetActor());
					return;
				}
				if(TraceHit.GetActor() == InteractionData.CurrentInteractable) {
					return;
				}
			}
		}
	}
	NoInteractableFound();
}
void ACpp_InventorySystemCharacter::FoundInteractable(AActor* NewInteractable) {
	// If char is already interacting with something, end the interaction
	if (IsInteracting()) {
		EndInteract();
	}
	// Remove focus from old interactable
	if(InteractionData.CurrentInteractable) {
		TargetInteractable = InteractionData.CurrentInteractable;
		TargetInteractable->EndFocus();
	}
	// Set new interactable
	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	HUD->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	// Begin focus on new interactable
	TargetInteractable->BeginFocus();
}
void ACpp_InventorySystemCharacter::NoInteractableFound() {
	// If char is interacting with something, end the interaction
	if(IsInteracting()) {
		GetWorldTimerManager().ClearTimer(TimerHandleInteraction);
	}
	if (InteractionData.CurrentInteractable) {
		// Remove focus from old interactable Incase it was destroyed right after being added
		if (IsValid(TargetInteractable.GetObject())) {
			TargetInteractable->EndFocus();
		}

		// Hide the interactable widget on the HUD
		HUD->HideInteractionWidget();

		// Clear the current interactable
		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}
void ACpp_InventorySystemCharacter::BeginInteract() {
	// Verify nothing has changed since the interaction check
	PerformInteractionCheck();

	if(InteractionData.CurrentInteractable) {
		if(IsValid(TargetInteractable.GetObject())) {
			TargetInteractable->BeginInteract();
			if(FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f)) {
				ACpp_InventorySystemCharacter::Interact();
			}
			else {
				// Set a timer to call the Interact function after the interaction duration
				GetWorldTimerManager().SetTimer(TimerHandleInteraction,
												this,
												&ACpp_InventorySystemCharacter::Interact,
												TargetInteractable->InteractableData.InteractionDuration, 
												false);

			} // Bug was fixed by re-adding the include for TimerManager.h
		}
	}
}
void ACpp_InventorySystemCharacter::EndInteract() {
	// Clear the timer
	GetWorldTimerManager().ClearTimer(TimerHandleInteraction);

	if(IsValid(TargetInteractable.GetObject())) {
		TargetInteractable->EndInteract();
	}
	
}
void ACpp_InventorySystemCharacter::Interact() {
	// Clear the timer
	GetWorldTimerManager().ClearTimer(TimerHandleInteraction);

	if(IsValid(TargetInteractable.GetObject())) {
		TargetInteractable->Interact(this);
	}
}

void ACpp_InventorySystemCharacter::ToggleMenu() {
	HUD->ToggleMenu();
}

void ACpp_InventorySystemCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
void ACpp_InventorySystemCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}