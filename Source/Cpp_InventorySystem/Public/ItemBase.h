// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ItemDataStructs.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class CPP_INVENTORYSYSTEM_API UItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	//=========================================================================================================================
	// PROPERTIES & VARIABLES
	//=========================================================================================================================

	/*UPROPERTY(VisibleAnywhere, Category = "Item Data")
	UInventoryComponent* OwningInventory;*/

	// UiMin and UiMax are used to min and max the value of the Quantity
	UPROPERTY(VisibleAnywhere, Category="Item Data", meta = (UIMin = 1, UIMax = 100))
	int32 Quantity;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FName ID;

	// Create Instance Variables
	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemAssetData ItemAssetData;


	//=========================================================================================================================
	// FUNCTIONS
	//=========================================================================================================================
	

	UItemBase();

	UItemBase* CreateItemCopy();
	
	// Getters
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericData.Weight; };

	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == ItemNumericData.MaxStackSize; };

	// Setters
	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	// Use Function
	UFUNCTION(Category = "Item")
	virtual void Use(ACpp_InventorySystemCharacter* Character);


protected:
	// Overridable == Function to be able to compare two Items
	bool operator==(const FName& OtherID) const {
		return ID == OtherID;
	}

};
