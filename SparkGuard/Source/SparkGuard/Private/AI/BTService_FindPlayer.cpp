// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_FindPlayer.h"

#include "AI/AIContro.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTService_FindPlayer::UBTService_FindPlayer()
{
	bNotifyBecomeRelevant=true;
	bNotifyCeaseRelevant=false;
	//节点刷新时间
	Interval=0.1f;
}

void UBTService_FindPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	AAIContro* AICon=Cast<AAIContro>(OwnerComp.GetAIOwner());
	if(!AICon)return;

	APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(AICon,0);
	if(!PlayerPawn)return;

	//更新黑板位置
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("PlayerLocation",PlayerPawn->GetActorLocation());
}
