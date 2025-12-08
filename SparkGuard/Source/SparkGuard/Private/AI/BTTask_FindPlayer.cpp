// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPlayer.h"

#include "AI/AIContro.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


UBTTask_FindPlayer::UBTTask_FindPlayer()
{
	NodeName="Find Player";
}

EBTNodeResult::Type UBTTask_FindPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIContro* AICon=Cast<AAIContro>(OwnerComp.GetAIOwner());
	if(!AICon)return EBTNodeResult::Failed;

	UBlackboardComponent* BB=AICon->GetBlackboardComponent();
	if(!BB)return EBTNodeResult::Failed;

	//获取玩家Pawn
	APawn* PlayerPawn=UGameplayStatics::GetPlayerPawn(AICon,0);
	if(!PlayerPawn)return EBTNodeResult::Failed;

	//写入黑板
	BB->SetValueAsObject("PlayerActor",PlayerPawn);
	BB->SetValueAsVector("PlayerLocation",PlayerPawn->GetActorLocation());

	return EBTNodeResult::Succeeded;
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
}
