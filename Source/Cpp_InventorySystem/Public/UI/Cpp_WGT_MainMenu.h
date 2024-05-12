// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_MainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
		ACpp_InventorySystemCharacter* PlayerCharacter;



protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


	

};
