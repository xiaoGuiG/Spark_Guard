// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparkGuardGameModeBase.h"
#include "CharacterActors/GemstoneCharacter.h"

ASparkGuardGameModeBase::ASparkGuardGameModeBase()
{
	ConstructorHelpers::FClassFinder<AGemstoneCharacter> GemStonePath(TEXT("Blueprint'/Game/SparkGuard/BluePrints/BP_GemStone.BP_GemStone_C'"));
	DefaultPawnClass=GemStonePath.Class;
}

void ASparkGuardGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
