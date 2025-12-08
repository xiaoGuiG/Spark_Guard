// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIContro.generated.h"

/**
 * 
 */
UCLASS()
class SPARKGUARD_API AAIContro : public AAIController
{
	GENERATED_BODY()
public:
	AAIContro();
	virtual void BeginPlay() override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UPROPERTY(EditDefaultsOnly,Category="AI")
	class UBehaviorTree* BehaviorTree;
};
