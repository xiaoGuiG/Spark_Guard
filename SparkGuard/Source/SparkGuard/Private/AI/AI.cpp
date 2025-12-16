// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AI.h"

#include "PaperFlipbookComponent.h"
#include "AI/AIContro.h"
#include "Bullet/Bullet.h"
#include "CharacterActors/GemstoneCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AAI::AAI()
{
	AIControllerClass=AAIContro::StaticClass();
	AutoPossessAI=EAutoPossessAI::PlacedInWorldOrSpawned;
	
	//创建攻击检测碰撞体
	AttackDetectionComponent=CreateDefaultSubobject<USphereComponent>(TEXT("AttackDetectionWidget"));
	AttackDetectionComponent->SetupAttachment(RootComponent);
	//创建血量UI组件
	HPWidget=CreateDefaultSubobject<UWidgetComponent>(TEXT("HPWidget"));
	HPWidget->SetupAttachment(GetSprite());

	//设置HPWidget的属性
	HPWidget->SetWidgetSpace(EWidgetSpace::Screen);//设置为屏幕UI模式
	HPWidget->SetDrawSize(FVector2D(100,10));//设置大小
	HPWidget->SetRelativeLocation(FVector(0,0,20));//调整位置
	
	
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
	AttackDetectionComponent->OnComponentBeginOverlap.AddDynamic(this,&AAI::AttackBeginEvent);
	AttackDetectionComponent->OnComponentEndOverlap.AddDynamic(this,&AAI::AttackEndEvent);
}

void AAI::BeginPlay()
{
	Super::BeginPlay();
	//初始化玩家类对象
	APawn* Player=UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	Guard=Cast<AGemstoneCharacter>(Player);
}

void AAI::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAI::AttackBeginEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor==Guard)
	{
		GetCharacterMovement()->MaxWalkSpeed=0;
		GetWorldTimerManager().SetTimer(AttackTimerHandle,this,&AAI::AttackGuard,1.f,true);
	}
}

void AAI::AttackEndEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor==Guard)
	{
		GetCharacterMovement()->MaxWalkSpeed=100.f;
		GetWorldTimerManager().ClearTimer(AttackTimerHandle);
	}
}

void AAI::BulletHitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!OtherActor||OtherActor==this)return;
	ABullet* Bullet=Cast<ABullet>(OtherActor);
	if(Bullet)
	{
		Bullet->Destroy();
		TakeBulletDamage(1.f);
		if(AIStats.CurrentHP==0.f)
		{
			Destroy();
		}
	}
}

void AAI::TakeBulletDamage(float Damage)
{
	AIStats.CurrentHP-=Damage;
}

void AAI::AttackGuard()
{
	if(Guard)
	{
		Guard->GuardStats.CurrentHP-=1.f;
	}
}





