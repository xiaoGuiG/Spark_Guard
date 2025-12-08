// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "AI.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAIStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHP=5.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHP=5.f;

};

UCLASS()
class SPARKGUARD_API AAI : public APaperCharacter
{
	GENERATED_BODY()
public:
	AAI();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//碰撞检测
	UFUNCTION()
	void BulletHitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	FAIStats AIStats;
};
