// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Cpp_AC_Inventory.generated.h"


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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	

protected:		
	//====================================================================================================================
	// PROPERTIES & VARIABLES
	//====================================================================================================================



	//====================================================================================================================
	// FUNCTIONS
	//====================================================================================================================
	
	virtual void BeginPlay() override;
};
