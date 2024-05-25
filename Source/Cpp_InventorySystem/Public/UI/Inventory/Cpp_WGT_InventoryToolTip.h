// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_InventoryToolTip.generated.h"

class UCpp_WGT_InventoryItemSlot;
class UTextBlock;

/**
 * 
 */
UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_InventoryToolTip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	UCpp_WGT_InventoryItemSlot* InventorySlotBeingHovered;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_ItemType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_DamageValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_ArmorRating;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_Usage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_ItemDescription;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_StackSize;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_SellValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_StackWeight;

protected:

	virtual void NativeConstruct() override;
};
