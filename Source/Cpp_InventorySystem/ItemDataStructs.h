#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

UENUM() // Rarity Of Item
enum class EItemQuality : uint8 { // DisplayNames are used in the editor for the enum values
	Common UMETA(DisplayName = "Common"),
	Uncommon UMETA(DisplayName = "Uncommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
};

UENUM() // Type Of Item
enum class EItemType : uint8 {
	Weapon UMETA(DisplayName = "Weapon"),
	Armor UMETA(DisplayName = "Armor"),
	Consumable UMETA(DisplayName = "Consumable"),
	Spell UMETA(DisplayName = "Spell"),
	Quest UMETA(DisplayName = "Quest"),
	Other UMETA(DisplayName = "Other"),
};

USTRUCT() // Item Statistics
struct FItemStatistics {	
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	float ArmorRating;
	
	UPROPERTY(EditAnywhere)
	float DamageValue;
	
	UPROPERTY(EditAnywhere)
	float RestorationValue;
	
	UPROPERTY(EditAnywhere)
	float SellValue;
};

USTRUCT() // Item Text Data
struct FItemTextData {	
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText ItemName;
	
	UPROPERTY(EditAnywhere)
	FText ItemDescription;

	UPROPERTY(EditAnywhere)
	FText InteractionText;

	UPROPERTY(EditAnywhere)
	FText UsageText;
};

USTRUCT() // Item Numeric Data
struct FItemNumericData {	
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int32 MaxStackSize;
	
	UPROPERTY(EditAnywhere)
	int32 Weight;

	UPROPERTY()
	bool bIsStackable;
};

USTRUCT() // Item Asset Data
struct FItemAssetData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh;
};

USTRUCT() // Item Data
struct FItemData : public FTableRowBase {
	// Generate Structure Body
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category="Item Data")
	FName ID;

	// Create Instance Variables
	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category="Item Data")
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FItemAssetData ItemAssetData;

};
