// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GuardController.generated.h"

/**
 * 
 */
UCLASS()
class SPARKGUARD_API AGuardController : public APlayerController
{
	GENERATED_BODY()
public:
	AGuardController();
	virtual void BeginPlay() override;
	bool GetMouseWorldDirection(FVector& OutWorldDir);
};
