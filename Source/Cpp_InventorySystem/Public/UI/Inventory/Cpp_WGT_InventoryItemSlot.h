// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_InventoryItemSlot.generated.h"

class UItemBase;

/**
 * 
 */
UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_InventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetItemReference(UItemBase* InItem) { ItemReference = InItem; };


protected:
	UPROPERTY(Category = "INventorySlot")
	UItemBase* ItemReference;

};
