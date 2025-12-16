// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AISpawner.generated.h"

UCLASS()
class SPARKGUARD_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//AI类
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAI> AIClass;
	//生成数量
	UPROPERTY(EditAnywhere)
	int32 SpawnCount=5;

	//生成位置
	UPROPERTY(EditAnywhere)
	float SpawnRadius=400.f;

	//生成时间
	UPROPERTY(EditAnywhere)
	float SpawnInterval=3.f;

	//生成函数
	FTimerHandle AISpawnHandle;
	void SpawnAI();
	
};
