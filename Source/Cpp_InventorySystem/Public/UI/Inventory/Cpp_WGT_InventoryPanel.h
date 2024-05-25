// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_InventoryPanel.generated.h"

// Forward Declarations
class UWrapBox;
class UTextBlock;
class ACpp_InventorySystemCharacter;
class UCpp_AC_Inventory;
class UCpp_WGT_InventoryItemSlot;

/**
 * 
 */
UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_InventoryPanel : public UUserWidget
{
	GENERATED_BODY()	
	
public:
	UFUNCTION()
	void RefreshInventory();

	UPROPERTY(meta = (BindWidget))
	UWrapBox* WB_InventoryPanel;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_WeightInfo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TB_CapacityInfo;

	UPROPERTY()
	ACpp_InventorySystemCharacter* PlayerCharacter;

	UPROPERTY()
	UCpp_AC_Inventory* InventoryReference;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCpp_WGT_InventoryItemSlot> InventoryItemSlotClass;


protected:

	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	void SetInfoText() const;
};
