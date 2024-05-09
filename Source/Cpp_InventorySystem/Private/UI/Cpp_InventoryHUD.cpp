// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Cpp_InventoryHUD.h"
#include "UI/Cpp_WGT_MainMenu.h"
#include "UI/Cpp_WGT_Interaction.h"

ACpp_InventoryHUD::ACpp_InventoryHUD() {

}

virtual void ACpp_InventoryHUD::BeginPlay() {
	Super::BeginPlay();

	if(MainMenuClass) {
		// Create the main menu widget based on the class
		MainMenuWidget = CreateWidget<UCpp_WGT_MainMenu>(GetWorld(), MainMenuClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	if(InteractionClass) {
		// Create the main menu widget based on the class
		InteractionWidget = CreateWidget<UCpp_WGT_Interaction>(GetWorld(), InteractionClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void ACpp_InventoryHUD::DisplayMenu() {
	if(MainMenuWidget) {
		bIsMenuVisible = true;
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ACpp_InventoryHUD::HideMenu() {
	if(MainMenuWidget) {
		bIsMenuVisible = false;
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

}

void ACpp_InventoryHUD::ShowInteractionWidget() {
	if(InteractionWidget) {
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}

}

void ACpp_InventoryHUD::HideInteractionWidget() {
	if(InteractionWidget) {
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

}

void ACpp_InventoryHUD::UpdateInteractionWidget(const FInteractableData* InteractableData) {
	if (InteractableWidget) {
		if(InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed) {
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		//InteractionWidget->UpdateWidget(InteractableData);
	}
}


