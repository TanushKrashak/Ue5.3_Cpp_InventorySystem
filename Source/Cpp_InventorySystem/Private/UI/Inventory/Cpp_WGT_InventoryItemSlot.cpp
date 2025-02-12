// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Cpp_WGT_InventoryItemSlot.h"
#include "UI/Inventory/Cpp_ItemDragDropOperation.h"
#include "UI/Inventory/Cpp_WGT_InventoryToolTip.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ItemBase.h"
#include "UI/Inventory/Cpp_WGT_DragItem.h"
#include "UI/Inventory/Cpp_ItemDragDropOperation.h"


void UCpp_WGT_InventoryItemSlot::NativeOnInitialized() {
	Super::NativeOnInitialized();
	
	if (ToolTipClass) {
		UCpp_WGT_InventoryToolTip* ToolTip = CreateWidget<UCpp_WGT_InventoryToolTip>(this, ToolTipClass);
		ToolTip->InventorySlotBeingHovered = this;
		SetToolTip(ToolTip);
	}

}

void UCpp_WGT_InventoryItemSlot::NativeConstruct() {
	Super::NativeConstruct();
	
	if (ItemReference) {
		switch (ItemReference->ItemQuality) {
			case EItemQuality::Common:
				Border_Item->SetBrushColor(FLinearColor::Gray);
				break;
			case EItemQuality::Uncommon:
				Border_Item->SetBrushColor(FLinearColor::Green);
				break;
			case EItemQuality::Rare:
				Border_Item->SetBrushColor(FLinearColor::Blue);
				break;
			case EItemQuality::Epic:
				Border_Item->SetBrushColor(FLinearColor(0.5f, 0.0f, 0.5f, 1.0f)); // Solid Purple Color
				break;
			case EItemQuality::Legendary:				
				Border_Item->SetBrushColor(FLinearColor(0.8f, 0.5f, 0.0f, 1.0f)); // Solid Orange Color
				break;		
			default: 
				break;
		}	

		IMG_Icon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		if (ItemReference->ItemNumericData.bIsStackable) {
			TXT_Quantity->SetText(FText::AsNumber(ItemReference->Quantity));
		}
		else {
			TXT_Quantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UCpp_WGT_InventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) {
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	if (DragItemVisualClass) {
		TObjectPtr<UCpp_WGT_DragItem> DragVisual = CreateWidget<UCpp_WGT_DragItem>(this, DragItemVisualClass);
		DragVisual->IMG_Icon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		DragVisual->Border_Item->SetBrushColor(Border_Item->GetBrushColor());
		DragVisual->TXT_Quantity->SetText(FText::AsNumber(ItemReference->Quantity));

		UCpp_ItemDragDropOperation* DragItemOperation = NewObject<UCpp_ItemDragDropOperation>();
		DragItemOperation->SourceItem = ItemReference;
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;
		
		DragItemOperation->DefaultDragVisual = DragVisual;
		DragItemOperation->Pivot = EDragPivot::TopLeft; // Tells it to drag from the top left corner of the widget

		OutOperation = DragItemOperation;
	}
}

FReply UCpp_WGT_InventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton) {
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	// Submenu On Right Click is not implemented yet

	return Reply.Unhandled();
}

void UCpp_WGT_InventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseLeave(InMouseEvent);
	
}

bool UCpp_WGT_InventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	 Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	 return true;
 }
