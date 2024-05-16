// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Interaction/Cpp_WGT_Interaction.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UCpp_WGT_Interaction::NativeConstruct() {
	Super::NativeConstruct();

	TXT_KeyPressText->SetText(FText::FromString("Press"));
	CurrentInteractionDuration = 0.0f;
}


UMG_API void UCpp_WGT_Interaction::NativeOnInitialized() {
	Super::NativeOnInitialized();

	// Percentage Delegate is used for updating the progress bar
	PB_Interaction->PercentDelegate.BindUFunction(this, "UpdateInteractionProgress");
}

void UCpp_WGT_Interaction::UpdateWidget(const FInteractableData* InteractableData) {
	switch(InteractableData->InteractableType) {
		case EInteractableType::Pickup:
			TXT_KeyPressText->SetText(FText::FromString("Press"));
			PB_Interaction->SetVisibility(ESlateVisibility::Collapsed);

			// Shows or Hides the Quantity TextBlock based on the quantity of the item
			if(InteractableData->Quantity == 1) {
				TXT_Quantity->SetVisibility(EVisibility::Collapsed);
			}
			else {
				TXT_Quantity->SetText(FText::Format(NSLOCTEXT("InteractionWidget", "TXT_Quantity", "x{0}"), InteractableData->Quantity));
				TXT_Quantity->SetVisibility(ESlateVisibility::Visible);
			}
			break;

		case EInteractableType::NonPlayerCharacter:
			break;

		case EInteractableType::Device:
			break;

		case EInteractableType::Toggle:
			break;
	
		case EInteractableType::Container:
			break;
	}
}

float UCpp_WGT_Interaction::UpdateInteractionProgress() {

	return 0.0f;
}

