// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SparkGuardGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPARKGUARD_API ASparkGuardGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASparkGuardGameModeBase();
	virtual void BeginPlay() override;
	
	//游戏结束
	UFUNCTION(BlueprintCallable)
	void GameOver();

	//游戏结束界面
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> GameOverWidgetClass;
};
