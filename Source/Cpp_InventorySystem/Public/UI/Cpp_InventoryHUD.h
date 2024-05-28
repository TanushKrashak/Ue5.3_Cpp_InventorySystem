// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Cpp_InventoryHUD.generated.h"

/**
 * 
 */

// Forward Declaration
class UCpp_WGT_MainMenu;
class UCpp_WGT_Interaction;
struct FInteractableData;


UCLASS()
class CPP_INVENTORYSYSTEM_API ACpp_InventoryHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	//=========================================================================================================================
	// PROPERTIES & VARIABLES
	//=========================================================================================================================

	// Makes it possible to create a widget in the HUD only of the specified class
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UCpp_WGT_MainMenu> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UCpp_WGT_Interaction> InteractionClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CrosshairClass;

	bool bIsMenuVisible = false;


	//=========================================================================================================================
	// FUNCTIONS
	//=========================================================================================================================
	
	ACpp_InventoryHUD();

	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowInteractionWidget();
	void HideInteractionWidget();
	void UpdateInteractionWidget(const FInteractableData* InteractableData);

protected:
	//=========================================================================================================================
	// PROPERTIES & VARIABLES
	//=========================================================================================================================

	UPROPERTY()
	UCpp_WGT_MainMenu* MainMenuWidget;

	UPROPERTY()
	UCpp_WGT_Interaction* InteractionWidget;

	UPROPERTY()
	UUserWidget* CrosshairWidget;

	//=========================================================================================================================
	// FUNCTIONS
	//=========================================================================================================================

	virtual void BeginPlay() override;

};
