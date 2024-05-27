// Fill out your copyright notice in the Description page of Project Settings.

// Game
#include "UI/Inventory/Cpp_WGT_InventoryPanel.h"
#include "../Cpp_InventorySystemCharacter.h"
#include "UI/Inventory/Cpp_WGT_InventoryItemSlot.h"
#include "Components/Cpp_AC_Inventory.h"
#include "ItemBase.h"
#include "UI/Inventory/Cpp_ItemDragDropOperation.h"

// Engine
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"




void UCpp_WGT_InventoryPanel::NativeOnInitialized() {
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<ACpp_InventorySystemCharacter>(GetOwningPlayerPawn());

	if (PlayerCharacter) {
		InventoryReference = PlayerCharacter->GetInventory();
		if (InventoryReference) {			
			// Call Refresh Inventory From Binding Delegate Of OnInventoryUpdated
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UCpp_WGT_InventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}

}

bool UCpp_WGT_InventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	const UCpp_ItemDragDropOperation* ItemDragDrop = Cast<UCpp_ItemDragDropOperation>(InOperation);
	
	if (InventoryReference && ItemDragDrop->SourceItem) {
		UE_LOG(LogTemp, Warning, TEXT("Item Dropped Over Inventory, Cancelling Drop"));
		// Returning True Cancels The Drop
		return true;
	}
	// Returning False Allows The Drop
	return false;
}

void UCpp_WGT_InventoryPanel::RefreshInventory() {	
	if (InventoryReference && InventoryItemSlotClass) {		
		WB_InventoryPanel->ClearChildren();		
		// Iterate Through Inventory
		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents()) {
			UCpp_WGT_InventoryItemSlot* ItemSlot = CreateWidget<UCpp_WGT_InventoryItemSlot>(this, InventoryItemSlotClass);
			ItemSlot->SetItemReference(InventoryItem);			
			WB_InventoryPanel->AddChildToWrapBox(ItemSlot);
		}	
		SetInfoText();
	}
}

void UCpp_WGT_InventoryPanel::SetInfoText() const {
	
	const FString WeightInfo = {"Weight: " + FString::SanitizeFloat(InventoryReference->GetInventoryTotalWeight()) + "kg / "
									  + FString::SanitizeFloat(InventoryReference->GetWeightCapacity()) + "kg"};
	TB_WeightInfo->SetText(FText::FromString(WeightInfo));

	const FString CapacityInfo = {"Capacity: " + FString::FromInt(InventoryReference->GetInventoryContents().Num()) + "/"
									  + FString::FromInt(InventoryReference->GetSlotsCapacity())};
	TB_CapacityInfo->SetText(FText::FromString(CapacityInfo));
}


