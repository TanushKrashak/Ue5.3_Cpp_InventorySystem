// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Cpp_WGT_InventoryToolTip.h"
#include "UI/Inventory/Cpp_WGT_InventoryItemSlot.h"
#include "ItemBase.h"
#include "Components/TextBlock.h"

void UCpp_WGT_InventoryToolTip::NativeConstruct() {
	Super::NativeConstruct();

	UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference();
	if (ItemBeingHovered) {
		switch (ItemBeingHovered->ItemType) {
			case EItemType::Weapon:
				break;
			case EItemType::Armor:
				break;
			case EItemType::Consumable:
				TXT_ItemType->SetText(FText::FromString("Consumable"));
				TXT_DamageValue->SetVisibility(ESlateVisibility::Collapsed);
				TXT_ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
				TXT_MaxStackSizeText->SetVisibility(ESlateVisibility::Collapsed);
				break;
			case EItemType::Spell:
				break;
			case EItemType::Quest:
				break;
			case EItemType::Other:
				TXT_ItemType->SetText(FText::FromString("Miscellaneous Item"));
				TXT_DamageValue->SetVisibility(ESlateVisibility::Collapsed);
				TXT_ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
				TXT_Usage->SetVisibility(ESlateVisibility::Collapsed);
				TXT_MaxStackSizeText->SetVisibility(ESlateVisibility::Collapsed);
				break;
			default:
				break;
		}

		TXT_ItemName->SetText(ItemBeingHovered->ItemTextData.ItemName);
		TXT_DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
		TXT_ArmorRating->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorRating));
		TXT_Usage->SetText(ItemBeingHovered->ItemTextData.UsageText);
		TXT_ItemDescription->SetText(ItemBeingHovered->ItemTextData.ItemDescription);
		TXT_StackWeight->SetText(FText::AsNumber(ItemBeingHovered->GetItemStackWeight()));

		if (ItemBeingHovered->ItemNumericData.bIsStackable) {
			TXT_MaxStackSize->SetText(FText::AsNumber(ItemBeingHovered->ItemNumericData.MaxStackSize));
		}
		else {
			TXT_MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}
