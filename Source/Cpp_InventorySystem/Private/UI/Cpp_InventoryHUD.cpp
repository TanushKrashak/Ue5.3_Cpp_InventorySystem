// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Cpp_InventoryHUD.h"
#include "UI/Cpp_WGT_MainMenu.h"
#include "UI/Interaction/Cpp_WGT_Interaction.h"

ACpp_InventoryHUD::ACpp_InventoryHUD() {

}

void ACpp_InventoryHUD::BeginPlay() {
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

	if (CrosshairClass) {
		// Create the crosshair
		CrosshairWidget = CreateWidget<UUserWidget>(GetWorld(), CrosshairClass);
		CrosshairWidget->AddToViewport(10);
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
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
void ACpp_InventoryHUD::ToggleMenu() {
	if (bIsMenuVisible) {
		HideMenu();
		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else {
		DisplayMenu();
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void ACpp_InventoryHUD::ShowCrosshair() {
	if (CrosshairWidget) {
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);		
	}
}
void ACpp_InventoryHUD::HideCrosshair() {
	if (CrosshairWidget) {
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);		
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
	if(InteractionWidget) {
		if(InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed) {
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		InteractionWidget->UpdateWidget(InteractableData);
	}
}

