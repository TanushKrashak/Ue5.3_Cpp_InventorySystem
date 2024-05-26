// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Cpp_ItemDragDropOperation.generated.h"

class UItemBase;
class UCpp_AC_Inventory;

UCLASS()
class CPP_INVENTORYSYSTEM_API UCpp_ItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UItemBase* SourceItem;
	
	UPROPERTY()
	UCpp_AC_Inventory* SourceInventory;
};
