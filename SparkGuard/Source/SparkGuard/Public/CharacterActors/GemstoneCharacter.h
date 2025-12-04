// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "GemstoneCharacter.generated.h"

/**
 * 
 */
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
	
};
