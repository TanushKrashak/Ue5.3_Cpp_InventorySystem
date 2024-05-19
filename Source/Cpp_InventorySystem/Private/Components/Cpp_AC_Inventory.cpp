// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Cpp_AC_Inventory.h"

// Constructor for the class.
UCpp_AC_Inventory::UCpp_AC_Inventory() {

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	
}

void UCpp_AC_Inventory::BeginPlay() {
	Super::BeginPlay();


}

void UCpp_AC_Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



UItemBase* UCpp_AC_Inventory::FindMatchingItem(UItemBase* InItem) const {
	if(InItem && InventoryContents.Contains(InItem)) {
		return InItem;		
	}
	return nullptr;
}

UItemBase* UCpp_AC_Inventory::FindNextItemByID(UItemBase* InItem) const {
	// Only works as overloaded operator is implemented in UItemBase for the == operator.
	// Element Type is used to get the type of the array elements.
	if(InItem && const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(InItem)) {
		return *Result;
	}
	return nullptr;
}

UItemBase* UCpp_AC_Inventory::FindNextPartialStack(UItemBase* InItem) const {
	// Summary Of If Statement:
	// Result is a pointer to the element type of the array UItemBase.
	// FindByPredicate is used to find the first element that satisfies the predicate.
	// FindByPredicate returns a pointer to the element type of the array UItemBase.
	// Lambda function is used to check if the ID of both are the same AND
	// if the item is not a full stack which means it can be added to
	// [&InItem] is the capture list for the lambda function which 
	// means it can access the InItem variable to compare it with the InventoryItem.
	// If the result is not null, return the result.
	if(const TArray<TObjectPtr<UItemBase>>::ElementType* Result = 
		InventoryContents.FindByPredicate([&InItem](const UItemBase* InventoryItem) {
				return InventoryItem->ID == InItem->ID && !InventoryItem->IsFullItemStack();
			}
		)) {
		return *Result;
	}
	return nullptr;
}

void UCpp_AC_Inventory::RemoveSingleInstanceOfItem(UItemBase* InItem) {

}

int32 UCpp_AC_Inventory::RemoveAmountOfItem(UItemBase* InItem, const int32 AmountToRemove) {

}

void UCpp_AC_Inventory::SplitExistingStack(UItemBase* InItem, const int32 AmountToSplit) {

}

FItemAddResult UCpp_AC_Inventory::HandleNonStackableItems(UItemBase* InItem, int32 AddAmount) {

}

int32 UCpp_AC_Inventory::HandleStackableItems(UItemBase* InItem, int32 AddAmount) {

}

int32 UCpp_AC_Inventory::CalculateWeightAddAmount(UItemBase* InItem, int32 AddAmount) {
	// Calculate the amount of weight that can be added to the inventory.
	// FloorToInt is used to round down the result of the division
	// eg. (90 - 55) / 10 = 3.5 -> FloorToInt(3.5) = 3
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) 
													   / InItem->GetItemSingleWeight());
	if(WeightMaxAddAmount >= AddAmount) {
		return AddAmount;
	}
	return WeightMaxAddAmount;
}

int32 UCpp_AC_Inventory::CalculateNumberForFullStack(UItemBase* InItem, int32 InitialAddAmount) {

}

FItemAddResult UCpp_AC_Inventory::HandleAddItem(UItemBase* InItem) {

}

void UCpp_AC_Inventory::AddNewItem(UItemBase* InItem, const int32 AddAmount) {

}

