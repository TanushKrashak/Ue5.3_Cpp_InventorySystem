// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Cpp_WGT_InventoryPanel.h"
#include "../Cpp_InventorySystemCharacter.h"
#include "Components/TextBlock.h"

void UCpp_WGT_InventoryPanel::NativeOnInitialized() {
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<ACpp_InventorySystemCharacter>(GetOwningPlayerPawn());

	if (PlayerCharacter) {
		InventoryReference = PlayerCharacter->GetInventory();
		if (InventoryReference) {
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UCpp_WGT_InventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
}

bool UCpp_WGT_InventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

}

void UCpp_WGT_InventoryPanel::RefreshInventory() {

}

void UCpp_WGT_InventoryPanel::SetInfoText() const {
	TB_WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"), 
										 InventoryReference->GetInventoryTotalWeight(),
										 InventoryReference->GetWeightCapacity()));
	TB_CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"),
										 InventoryReference->GetInventoryContents().Num(),
										 InventoryReference->GetSlotsCapacity()));
}


