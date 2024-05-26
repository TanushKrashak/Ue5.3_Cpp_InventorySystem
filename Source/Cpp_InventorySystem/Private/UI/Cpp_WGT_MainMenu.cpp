#include "UI/Cpp_WGT_MainMenu.h"
#include "UI/Inventory/Cpp_ItemDragDropOperation.h"
#include "../Cpp_InventorySystemCharacter.h"

void UCpp_WGT_MainMenu::NativeOnInitialized() {
	Super::NativeOnInitialized();
}

void UCpp_WGT_MainMenu::NativeConstruct() {
	Super::NativeConstruct();
	// Cast to the player character
	PlayerCharacter = Cast<ACpp_InventorySystemCharacter>(GetOwningPlayerPawn());
}

bool UCpp_WGT_MainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {	

	const UCpp_ItemDragDropOperation* ItemDragDrop = Cast<UCpp_ItemDragDropOperation>(InOperation);
	if (PlayerCharacter && ItemDragDrop->SourceItem) {
		PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		return true;
	}

	return false;
}


