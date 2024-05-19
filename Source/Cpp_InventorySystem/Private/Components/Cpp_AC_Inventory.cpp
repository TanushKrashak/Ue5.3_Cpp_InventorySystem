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

