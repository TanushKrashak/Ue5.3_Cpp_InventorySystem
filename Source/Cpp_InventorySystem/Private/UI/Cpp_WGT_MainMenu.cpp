#include "UI/Cpp_WGT_MainMenu.h"
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
		
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}


