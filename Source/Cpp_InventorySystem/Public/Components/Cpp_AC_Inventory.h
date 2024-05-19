// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpp_AC_Inventory.generated.h"

UENUM(BlueprintType)
enum class EItemAddResult : uint8 {
	IAR_NoItemsAdded UMETA(DisplayName = "No Items Added"),
	IAR_SomeItemsAdded UMETA(DisplayName = "Some Items Added"),
	IAR_AllItemsAdded UMETA(DisplayName = "All Items Added")
};

USTRUCT(BlueprintType)
struct FItemAddResult {
	GENERATED_BODY()

	FItemAddResult() :
		ActualAmountAdded(0),
		OperationResult(EItemAddResult::IAR_NoItemsAdded),
		ResultMessage(FText::GetEmpty())
	{};

	// Actual amount of items that was added to the inventory
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;
	// Enum value indicating the result of the add item operation
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;
	// Informational message about the result of the add item operation
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage;

	// Static methods as they are not dependent on the state of the object
	static FItemAddResult AddedNone(const FText& ErrorText) {
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemsAdded;
		AddedNoneResult.ResultMessage = ErrorText;
		return AddedNoneResult;
	}
	static FItemAddResult AddedSome(const int32 SomeAmountAdded, const FText& ErrorText) {
		FItemAddResult AddedSomeResult;
		AddedSomeResult.ActualAmountAdded = SomeAmountAdded;
		AddedSomeResult.OperationResult = EItemAddResult::IAR_SomeItemsAdded;
		AddedSomeResult.ResultMessage = ErrorText;
		return AddedSomeResult;
	}
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message) {
		FItemAddResult AddedAllResult;
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemsAdded;
		AddedAllResult.ResultMessage = Message;
		return AddedAllResult;
	}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_INVENTORYSYSTEM_API UCpp_AC_Inventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	//====================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================



	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================

	UCpp_AC_Inventory();	

		
	

protected:		
	//====================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================



	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
