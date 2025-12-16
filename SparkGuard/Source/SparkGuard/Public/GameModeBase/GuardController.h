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
	//获取鼠标世界坐标
	bool GetMouseWorldDirection(FVector& OutWorldDir);

	//添加GuardUI
	UPROPERTY(EditAnywhere,Category="UI")
	TSubclassOf<UUserWidget> GuardUIClass;

	UUserWidget* GuardUI;
};
