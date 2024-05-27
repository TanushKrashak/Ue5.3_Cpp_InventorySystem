// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "Components/Cpp_AC_Inventory.h"

UItemBase::UItemBase() {
	bIsCopy = false;
	bIsPickup = true;
}

UItemBase* UItemBase::CreateItemCopy()
{	
    UItemBase* NewItem = NewObject<UItemBase>(GetTransientPackage(), UItemBase::StaticClass());
    if (NewItem) {		     
        NewItem->Quantity = Quantity;
        NewItem->ID = ID;
        NewItem->ItemType = ItemType;
        NewItem->ItemQuality = ItemQuality;
        NewItem->ItemStatistics = ItemStatistics;
        NewItem->ItemTextData = ItemTextData;
        NewItem->ItemNumericData = ItemNumericData;
        NewItem->ItemAssetData = ItemAssetData;
		NewItem->bIsCopy = true;
    }
    return NewItem;
}

void UItemBase::ResetItemFlags() {
	bIsCopy = false;
	bIsPickup = false;
}

void UItemBase::SetQuantity(const int32 NewQuantity) {
	if (NewQuantity != Quantity) {
		// Clamp the quantity to be between 0 and the max stack size only if the item is stackable
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericData.bIsStackable ? ItemNumericData.MaxStackSize : 1);

		if(OwningInventory) {
			if(Quantity == 0) {
				OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}
	}
}

void UItemBase::Use(ACpp_InventorySystemCharacter* Character) {

}
