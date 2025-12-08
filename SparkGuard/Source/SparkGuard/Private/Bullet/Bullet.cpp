// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/Bullet.h"

#include "PaperFlipbookComponent.h"
#include "AI/AI.h"
#include "Components/SphereComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//构建组件
	BulletSprite=CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	BulletSphere=CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent=BulletSphere;
	//绑定组件关系
	BulletSprite->SetupAttachment(RootComponent);

	//设置检测体检测范围与性质
	/*BulletSphere->SetGenerateOverlapEvents(true);
	BulletSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);//只检测overlap，不阻挡任何物体
	BulletSphere->SetCollisionObjectType(ECC_WorldDynamic);//默认使用overlap全部物体
	BulletSphere->SetCollisionResponseToAllChannels(ECR_Overlap);*/


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle,this,&ABullet::DestroyActor,LifeTime,false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!MoveDirection.IsNearlyZero())
	{
		FVector NewPos=GetActorLocation()+MoveDirection*Speed*DeltaTime;
		SetActorLocation(NewPos,true);
	}
}

void ABullet::InitBullet(FVector Dir)
{
	MoveDirection=Dir;
}

void ABullet::DestroyActor()
{
	Destroy();
}









