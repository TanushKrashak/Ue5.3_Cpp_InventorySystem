// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Pickup.h"
#include "ItemBase.h"
#include "Engine/DataTable.h"
#include "Components/Cpp_AC_Inventory.h"
#include "../Cpp_InventorySystemCharacter.h"



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
	if(!ItemRowHandle.IsNull()) {
		// Get the item data from the data table using the DesiredItemID
		const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString());

		ItemReference = NewObject<UItemBase>(this, BaseClass);
		
		ItemReference->ID = ItemData->ID;
		ItemReference->ItemQuality = ItemData->ItemQuality;
		ItemReference->ItemTextData = ItemData->ItemTextData;
		ItemReference->ItemType = ItemData->ItemType;
		ItemReference->ItemAssetData = ItemData->ItemAssetData;
		ItemReference->ItemNumericData = ItemData->ItemNumericData;
		ItemReference->ItemStatistics = ItemData->ItemStatistics;
		// Sets whether the item is stackable or not 
		ItemReference->ItemNumericData.bIsStackable = ItemData->ItemNumericData.MaxStackSize > 1;
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
	ItemReference->OwningInventory = nullptr;
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
			if(UCpp_AC_Inventory* PlayerInventory = Taker->GetInventory()) {
				const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);
				switch(AddResult.OperationResult) {
					case EItemAddResult::IAR_NoItemsAdded:
						break;
					case EItemAddResult::IAR_SomeItemsAdded:						
						UpdateInteractableData();
						Taker->UpdateInteractionWidget();
						break;
					case EItemAddResult::IAR_AllItemsAdded:
						Destroy();
						break;
				}
				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString());
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Player Inventory is null!"));
			}			
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Pickup Internal Reference is null!"));
		}
	}
}

#if WITH_EDITOR
void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) {
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if(ChangedPropertyName == GET_MEMBER_NAME_CHECKED(FDataTableRowHandle, RowName)) {
		if(!ItemRowHandle.IsNull()) {			
			if(const FItemData* ItemData = ItemRowHandle.GetRow<FItemData>(ItemRowHandle.RowName.ToString())) {
				PickupMesh->SetStaticMesh(ItemData->ItemAssetData.Mesh);
			}
		}
	}
}
#endif

