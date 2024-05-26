// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_InventoryItemSlot.generated.h"

// Forward Declarations
class UItemBase;
class UCpp_WGT_DragItem;
class UCpp_WGT_InventoryToolTip;
class UBorder;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_InventoryItemSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetItemReference(UItemBase* InItem) { ItemReference = InItem; };
	FORCEINLINE UItemBase* GetItemReference() const { return ItemReference; };
	
	virtual const UE::FieldNotification::IClassDescriptor* GetClassDescriptor() const {
		return GetClassDescriptor();
	}

protected:
	UPROPERTY(EditDefaultsOnly, Category = "InventorySlot")
	TSubclassOf<UCpp_WGT_DragItem> DragItemVisualClass;

	UPROPERTY(EditDefaultsOnly, Category = "InventorySlot")
	TSubclassOf<UCpp_WGT_InventoryToolTip> ToolTipClass;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlot")
	UItemBase* ItemReference;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlot", meta = (BindWidget))
	UBorder* Border_Item;
	
	UPROPERTY(VisibleAnywhere, Category = "InventorySlot", meta = (BindWidget))
	UImage* IMG_Icon;

	UPROPERTY(VisibleAnywhere, Category = "InventorySlot", meta = (BindWidget))
	UTextBlock* TXT_Quantity;

	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;







};
