// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeBase/GuardController.h"

#include "Blueprint/UserWidget.h"

AGuardController::AGuardController()
{
	//为什么设置鼠标功能写在构造函数里没用

}

void AGuardController::BeginPlay()
{
	Super::BeginPlay();

	//设置鼠标
	bShowMouseCursor=true;
	bEnableClickEvents=true;
	bEnableMouseOverEvents=true;

	//添加GuardUI到视口中
	if(GuardUIClass)
	{
		GuardUI=CreateWidget<UUserWidget>(this,GuardUIClass);
		if(GuardUI)
		{
			GuardUI->AddToViewport();
		}
	}
}

bool AGuardController::GetMouseWorldDirection(FVector& OutWorldDir)
{
	float MouseX,MouseY;
	if(!GetMousePosition(MouseX,MouseY))
	{
		return false;
	}
	FVector WorldLocation;
	return DeprojectScreenPositionToWorld(MouseX,MouseY,WorldLocation,OutWorldDir);
}
