// Fill out your copyright notice in the Description page of Project Settings.

// Game
#include "UI/Inventory/Cpp_WGT_InventoryPanel.h"
#include "../Cpp_InventorySystemCharacter.h"
#include "UI/Inventory/Cpp_WGT_InventoryItemSlot.h"
#include "Components/Cpp_AC_Inventory.h"
#include "ItemBase.h"

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
	// Add a 10 second timer to refresh the inventory
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCpp_WGT_InventoryPanel::RefreshInventory, 3.0f, true);

}

bool UCpp_WGT_InventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return true;
}

void UCpp_WGT_InventoryPanel::RefreshInventory() {	
	if (InventoryReference && InventoryItemSlotClass) {
		UE_LOG(LogTemp, Warning, TEXT("RefreshInventory Called"));
		WB_InventoryPanel->ClearChildren();		
		// Iterate Through Inventory
		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents()) {
			UCpp_WGT_InventoryItemSlot* ItemSlot = CreateWidget<UCpp_WGT_InventoryItemSlot>(this, InventoryItemSlotClass);
			ItemSlot->SetItemReference(InventoryItem);			
			WB_InventoryPanel->AddChildToWrapBox(ItemSlot);
		}	
	}
}

void UCpp_WGT_InventoryPanel::SetInfoText() const {
	TB_WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"), 
										 InventoryReference->GetInventoryTotalWeight(),
										 InventoryReference->GetWeightCapacity()));
	TB_CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
										 InventoryReference->GetInventoryContents().Num(),
										 InventoryReference->GetSlotsCapacity()));
}


