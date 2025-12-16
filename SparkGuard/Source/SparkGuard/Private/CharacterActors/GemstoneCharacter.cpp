// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterActors/GemstoneCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Bullet/Bullet.h"
#include "GameModeBase/GuardController.h"
#include "Kismet/GameplayStatics.h"
#include "SparkGuard/SparkGuardGameModeBase.h"

AGemstoneCharacter::AGemstoneCharacter()
{
	//启用Tick
	PrimaryActorTick.bCanEverTick=true;
	
	//相机初始化
	Arm=CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Arm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(Arm);
	Arm->bDoCollisionTest=false;
	Arm->SetRelativeRotation(FRotator(-90,-90,0));
	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);//相机正交模式
	Camera->SetOrthoWidth(800.f);

	//禁止物理加速度
	GetCharacterMovement()->MaxAcceleration=999999.f;//瞬间加速为目标速度
	GetCharacterMovement()->BrakingDecelerationWalking=999999.f;//瞬间减速为0
	GetCharacterMovement()->GroundFriction=0.f;//关闭摩擦
	GetCharacterMovement()->BrakingFrictionFactor=0.f;//关闭刹车摩擦
}

void AGemstoneCharacter::BeginPlay()
{
	Super::BeginPlay();
	//绑定轴映射
	InputComponent->BindAxis(TEXT("MoveY"),this,&AGemstoneCharacter::GuardMoveUp);
	InputComponent->BindAxis(TEXT("MoveX"),this,&AGemstoneCharacter::GuardMoveRight);
	//绑定操作映射
	InputComponent->BindAction(TEXT("Attack"),EInputEvent::IE_Pressed,this,&AGemstoneCharacter::GuardAttack);
}

void AGemstoneCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//角色移动
	GuardMove();
}

void AGemstoneCharacter::GuardMoveUp(float AxisValue)
{
	AddMovementInput(FVector(0,AxisValue*0.4,0));
}

void AGemstoneCharacter::GuardMoveRight(float AxisValue)
{
	AddMovementInput(FVector(AxisValue*0.4,0,0));
}

void AGemstoneCharacter::GuardMove()
{
	//移动动画切换
	if(GetCharacterMovement()->Velocity.IsZero())
	{
		GetSprite()->SetFlipbook(Idel_PFb);
	}
	else
	{
		GetSprite()->SetFlipbook(Run_PFb);
	}
}

void AGemstoneCharacter::GuardAttack()
{

	//生成子弹
	FVector SpawnLoc=GetActorLocation();
	FRotator SpawnRot=FRotator::ZeroRotator;
	//配置子弹从属关系
	FActorSpawnParameters Params;
	Params.Instigator=this;
	Params.Owner=this;

	ABullet* Bullet=GetWorld()->SpawnActor<ABullet>(BulletClass,SpawnLoc,SpawnRot,Params);
	if(Bullet)
	{
		FVector Dir=GetAttackDir();
		Bullet->InitBullet(Dir);
	}
}

FVector AGemstoneCharacter::GetAttackDir()
{
	//获取初始生成位置
	FVector SpawnLoc=GetActorLocation();
	//获取鼠标世界位置
	AGuardController* PC=Cast<AGuardController>(GetController());
	if(!PC)return FVector::ZeroVector;
	//鼠标在世界中的位置
	float MouseX,MouseY;
	PC->GetMousePosition(MouseX,MouseY);
	FVector WorldPos,WorldRot;
	PC->DeprojectScreenPositionToWorld(MouseX,MouseY,WorldPos,WorldRot);
	//计算射击方向
	FVector Dir=WorldPos-SpawnLoc;
	Dir.Z=0;
	Dir.Normalize();
	return Dir;
}

void AGemstoneCharacter::IsDeath()
{
	ASparkGuardGameModeBase* GM=Cast<ASparkGuardGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if(GM)
	{
		GM->GameOver();
	}
}
