// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Cpp_WGT_DragItem.generated.h"

// Forward Declarations
class UBorder;
class UImage;
class UTextBlock;

UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_WGT_DragItem : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Drag Item", meta = (BindWidget))
	UBorder* Border_Item;
	
	UPROPERTY(VisibleAnywhere, Category = "Drag Item", meta = (BindWidget))
	UImage* IMG_Icon;

	UPROPERTY(VisibleAnywhere, Category = "Drag Item", meta = (BindWidget))
	UTextBlock* TXT_Quantity;
};
