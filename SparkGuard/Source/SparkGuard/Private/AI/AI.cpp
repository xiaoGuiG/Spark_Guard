// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI.h"

#include "PaperFlipbookComponent.h"
#include "AI/AIContro.h"
#include "Bullet/Bullet.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAI::AAI()
{
	AIControllerClass=AAIContro::StaticClass();
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;
	
	//禁用重力
	GetCharacterMovement()->GravityScale=0;
	GetCharacterMovement()->bConstrainToPlane=true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0,0,1));
	/*
	//碰撞体检测
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);*/

	//绑定碰撞
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this,&AAI::BulletHitEvent);
}

void AAI::BeginPlay()
{
	Super::BeginPlay();
}

void AAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AAI::BulletHitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor||OtherActor==this)return;
	ABullet* Bullet=Cast<ABullet>(OtherActor);
	if(Bullet)
	{
		Bullet->Destroy();
		Destroy();
	}
}
