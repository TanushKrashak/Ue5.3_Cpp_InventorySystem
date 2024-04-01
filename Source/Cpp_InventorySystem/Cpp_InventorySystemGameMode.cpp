// Copyright Epic Games, Inc. All Rights Reserved.

#include "Cpp_InventorySystemGameMode.h"
#include "Cpp_InventorySystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACpp_InventorySystemGameMode::ACpp_InventorySystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
