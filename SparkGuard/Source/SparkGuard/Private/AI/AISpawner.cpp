// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AISpawner.h"

#include "NavigationSystem.h"
#include "AI/AI.h"

// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	if(AIClass)
	{
		GetWorldTimerManager().SetTimer(AISpawnHandle,this,&AAISpawner::SpawnAI,SpawnInterval,true);
	}
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAISpawner::SpawnAI()
{
	if(!AIClass)return;
	UNavigationSystemV1* NavSys=UNavigationSystemV1::GetCurrent(GetWorld());
	if(!NavSys)return;

	FNavLocation NavLoc;
	bool bFound=NavSys->GetRandomReachablePointInRadius(GetActorLocation(),SpawnRadius,NavLoc);

	if(!bFound)return;

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AAI>(AIClass,NavLoc.Location,FRotator::ZeroRotator,Params);
}

