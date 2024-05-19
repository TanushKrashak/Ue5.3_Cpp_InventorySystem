// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../ItemDataStructs.h"
#include "ItemBase.generated.h"

class UCpp_AC_Inventory;

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

	UPROPERTY(VisibleAnywhere, Category = "Item Data")
		UCpp_AC_Inventory* OwningInventory;

	// UiMin and UiMax are used to min and max the value of the Quantity
	UPROPERTY(VisibleAnywhere, Category="Item")
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category="Item")
	FName ID;

	// Create Instance Variables
	UPROPERTY(VisibleAnywhere, Category="Item")
	EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category="Item")
	EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category="Item")
	FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category="Item")
	FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category="Item")
	FItemNumericData ItemNumericData;

	UPROPERTY(VisibleAnywhere, Category="Item")
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
		return this->ID == OtherID;
	}

};
