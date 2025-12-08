// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI.h"

#include "PaperFlipbookComponent.h"
#include "AI/AIContro.h"
#include "GameFramework/CharacterMovementComponent.h"

AAI::AAI()
{
	AIControllerClass=AAIContro::StaticClass();
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;

	//禁用重力
	GetCharacterMovement()->GravityScale=0;
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0,0,1));
	
	
}

void AAI::BeginPlay()
{
	Super::BeginPlay();
}

void AAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}
