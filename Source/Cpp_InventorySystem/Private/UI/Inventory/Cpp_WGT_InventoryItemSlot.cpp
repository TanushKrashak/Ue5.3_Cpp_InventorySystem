// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Inventory/Cpp_WGT_InventoryItemSlot.h"

const UE::FieldNotification::IClassDescriptor& UCpp_WGT_InventoryItemSlot::GetFieldNotificationDescriptor() const {
	
}


void UCpp_WGT_InventoryItemSlot::NativeOnInitialized() {
	Super::NativeOnInitialized();

}
void UCpp_WGT_InventoryItemSlot::NativeConstruct() {
	Super::NativeConstruct();
	
}
void UCpp_WGT_InventoryItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) {
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
}
FReply UCpp_WGT_InventoryItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
}
void UCpp_WGT_InventoryItemSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent) {
	Super::NativeOnMouseLeave(InMouseEvent);
	
}
bool UCpp_WGT_InventoryItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) {
	 Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

 }
