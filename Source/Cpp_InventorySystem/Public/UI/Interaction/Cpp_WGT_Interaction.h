// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_Interaction.generated.h"

/**
 * 
 */

// Forward Declaration
class ACpp_InventorySystemCharacter;
struct FInteractableData;
class UTextBlock;
class UProgressBar;

UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_Interaction : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category="Interaction Widget | Player Reference")
	ACpp_InventorySystemCharacter* PlayerCharacter;

	void UpdateWidget(const FInteractableData* InteractableData);

protected:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* TXT_Name;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* TXT_Action;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* TXT_Quantity;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UTextBlock* TXT_KeyPressText;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Interactable Data")
	UProgressBar* PB_Interaction;

	float CurrentInteractionDuration;

	UFUNCTION(Category = "Interaction Widget | Interactable Data")
	float UpdateInteractionProgress();


	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

};
