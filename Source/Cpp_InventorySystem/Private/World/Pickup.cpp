// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Pickup.h"
#include "ItemBase.h"
#include "Engine/DataTable.h"


// Sets default values
APickup::APickup() {
	PrimaryActorTick.bCanEverTick = false;

	// Create the Pickup Mesh Component and set it as the root component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetSimulatePhysics(true);
	SetRootComponent(PickupMesh);
}

void APickup::BeginPlay() {
	Super::BeginPlay();

	InitializePickup(UItemBase::StaticClass(), ItemQuantity);
}



void APickup::InitializePickup(const TSubclassOf<UItemBase> BaseClass, const int32 InQuantity) {
	if(ItemDataTable && !DesiredItemID.IsNone()) {
		// Get the item data from the data table using the DesiredItemID
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);
		
		ItemReference->ID = ItemData->ID;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->ItemTextData = ItemData->ItemTextData;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemAssetData = ItemData->ItemAssetData;
		ItemReference->ItemNumericData = ItemData->ItemNumericData;
		ItemReference->ItemStatistics = ItemData->ItemStatistics;

		// Set the quantity of the item
		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);

		UpdateInteractableData();
	}
}

void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity) {
	ItemReference = ItemToDrop;
	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);
	// Set the weight of the item to the single weight of the item
	ItemReference->ItemNumericData.Weight = ItemToDrop->GetItemSingleWeight();
	PickupMesh->SetStaticMesh(ItemToDrop->ItemAssetData.Mesh);

	UpdateInteractableData();

}

void APickup::UpdateInteractableData() {
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemReference->ItemTextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->ItemTextData.ItemName;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	InteractableData = InstanceInteractableData;
}

void APickup::BeginFocus() {
	if(PickupMesh) {
		PickupMesh->SetRenderCustomDepth(true);
	}
}

void APickup::EndFocus() {
	if(PickupMesh) {
		PickupMesh->SetRenderCustomDepth(false);
	}
}

void APickup::Interact(ACpp_InventorySystemCharacter* PlayerChracter) {
	if(PlayerChracter) {
		TakePickup(PlayerChracter);
	}
}

void APickup::TakePickup(const ACpp_InventorySystemCharacter* Taker) {
	if(!IsPendingKillPending()) {
		if(ItemReference) {
			//if (UInventoryComponent* PlayerInventory = Taker->GetInventory

			// Try To Add the item to the inventory
			// based on the result, adjust or destroy the pickup
		}
	}
}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if(ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemID)) {
		if(ItemDataTable) {			
			if(const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString())) {
				PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
			}
		}
	}
}

