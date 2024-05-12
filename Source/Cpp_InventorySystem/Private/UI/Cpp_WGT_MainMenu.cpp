#include "UI/Cpp_WGT_MainMenu.h"

void UCpp_WGT_MainMenu::NativeConstruct() {
	Super::NativeConstruct();
	// Cast to the player character
	PlayerCharacter = Cast<ACpp_InventorySystemCharacter>(GetOwningPlayerPawn());
}

void UCpp_WGT_MainMenu::NativeOnInitialized() {
	Super::NativeOnInitialized();
}

bool UCpp_WGT_MainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {

	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	// Cast Operation to item drag drop, ensure player is valid, and call the drop function
}


