// Copyright Epic Games, Inc. All Rights Reserved.


#include "SparkGuardGameModeBase.h"
#include "CharacterActors/GemstoneCharacter.h"

ASparkGuardGameModeBase::ASparkGuardGameModeBase()
{
	//加载游戏模式
	ConstructorHelpers::FClassFinder<AGemstoneCharacter> GemStonePath(TEXT("Blueprint'/Game/SparkGuard/Characters/BP_GemStone.BP_GemStone_C'"));
	DefaultPawnClass=GemStonePath.Class;
	ConstructorHelpers::FClassFinder<APlayerController> GuardControPath(TEXT("Blueprint'/Game/SparkGuard/BluePrints/GameModeBase/BP_GuardController.BP_GuardController_C'"));
	PlayerControllerClass=GuardControPath.Class;
}

void ASparkGuardGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
