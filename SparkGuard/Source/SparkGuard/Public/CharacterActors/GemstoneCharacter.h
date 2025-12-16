// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GemstoneCharacter.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGuardStats
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float MaxHP=10.f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentHP=10.f;
}; 
 
UCLASS()
class SPARKGUARD_API AGemstoneCharacter : public APaperCharacter
{
	GENERATED_BODY()
public:
	AGemstoneCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//相机组件
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* Arm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	//角色移动
	void GuardMoveUp(float AxisValue);
	void GuardMoveRight(float AxisValue);
	void GuardMove();

	//PaperFlipbook资产
	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* Idel_PFb;
	UPROPERTY(EditAnywhere)
	class UPaperFlipbook* Run_PFb;

	//子弹类
	UPROPERTY(EditAnywhere,Category="Bullet")
	TSubclassOf<class ABullet> BulletClass;
	
	//角色攻击
	void GuardAttack();

	//获取子弹运动方向
	FVector GetAttackDir();

	//Guard属性结构体
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	FGuardStats GuardStats;

	//角色死亡
	UFUNCTION()
	void IsDeath();
};
