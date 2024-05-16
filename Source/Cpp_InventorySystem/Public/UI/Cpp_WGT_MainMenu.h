#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_MainMenu.generated.h"

// Forward declaration
class ACpp_InventorySystemCharacter; 

UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_MainMenu : public UUserWidget {
	GENERATED_BODY()
public:
	UPROPERTY()
		ACpp_InventorySystemCharacter* PlayerCharacter;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
