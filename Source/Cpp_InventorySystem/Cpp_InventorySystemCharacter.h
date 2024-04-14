// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "InteractionInterface.h"
#include "Cpp_InventorySystemCharacter.generated.h"

USTUCT()
struct FInteractionData {
	GENERATED_USTRUCT_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.0f) {};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

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

protected:
	//=========================================================================================================================
	// PROPERTIES & VARIABLES
	//=========================================================================================================================

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

	// The Character | is for organization purposes
	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;


	float InteractionFrequency;
	
	float InteractionCheckDistance;

	FTimerHandle TimerHandleInteraction;

	FInteractionData InteractionData;


	//=========================================================================================================================
	// FUNCTIONS
	//=========================================================================================================================

	void PerformInteractionCheck();
	void FoundInteractable(AActor* Interactables);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();


	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);			

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;
};

