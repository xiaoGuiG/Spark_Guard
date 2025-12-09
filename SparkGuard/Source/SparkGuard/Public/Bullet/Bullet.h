// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class SPARKGUARD_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//构建Paper2D组件
	UPROPERTY(EditAnywhere)
	class UPaperFlipbookComponent* BulletSprite;
	UPROPERTY(EditAnywhere)
	class USphereComponent* BulletSphere;

	//设置移动方向和速度
	UPROPERTY(EditAnywhere)
	float Speed=1000.f;
	FVector MoveDirection;
	void InitBullet(FVector Dir);

	//设置生命周期
	float LifeTime=4.f;
	void DestroyActor();

	
};
