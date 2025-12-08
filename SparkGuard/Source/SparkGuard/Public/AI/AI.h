// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "AI.generated.h"

/**
 * 
 */
UCLASS()
class SPARKGUARD_API AAI : public APaperCharacter
{
	GENERATED_BODY()
public:
	AAI();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
};
