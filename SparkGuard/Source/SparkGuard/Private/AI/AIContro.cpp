// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIContro.h"

AAIContro::AAIContro()
{
	
}

void AAIContro::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIContro::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	//运行行为树
	if(BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
	//禁止控制器控制ai类在yaw方向上旋转
	InPawn->bUseControllerRotationYaw=false;

}
