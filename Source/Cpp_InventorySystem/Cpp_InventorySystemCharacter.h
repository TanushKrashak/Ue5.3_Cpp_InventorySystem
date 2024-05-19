// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/InteractionInterface.h"
#include "Cpp_InventorySystemCharacter.generated.h"



USTRUCT()
struct FInteractionData {
	GENERATED_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f) {};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};

// Forward Declaration
class ACpp_InventoryHUD;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UCpp_AC_Inventory;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACpp_InventorySystemCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//=========================================================================================================================
	// PROPERTIES & VARIABLES
	//=========================================================================================================================

	


	//=========================================================================================================================
	// FUNCTIONS
	//=========================================================================================================================
	ACpp_InventorySystemCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	// Returns whether the character is currently interacting with an interactable
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandleInteraction); }

	FORCEINLINE UCpp_AC_Inventory* GetInventory() const { return PlayerInventory; }

protected:
	//=========================================================================================================================
	// PROPERTIES & VARIABLES
	//=========================================================================================================================

	UPROPERTY()
	ACpp_InventoryHUD* HUD;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	// The Character | is for organization purposes
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Character | Inventory")
	UCpp_AC_Inventory* PlayerInventory;

	float InteractionFrequency;
	
	float InteractionCheckDistance;

	FTimerHandle TimerHandleInteraction;

	FInteractionData InteractionData;


	//=========================================================================================================================
	// FUNCTIONS
	//=========================================================================================================================

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);			
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;
};

