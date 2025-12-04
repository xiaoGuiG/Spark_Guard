// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterActors/GemstoneCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

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
	InputComponent->BindAxis(TEXT("MoveY"),this,&AGemstoneCharacter::GuardMoveUp);
	InputComponent->BindAxis(TEXT("MoveX"),this,&AGemstoneCharacter::GuardMoveRight);
}

void AGemstoneCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GuardMove();
}

void AGemstoneCharacter::GuardMoveUp(float AxisValue)
{
	AddMovementInput(FVector(0,AxisValue,0));
}

void AGemstoneCharacter::GuardMoveRight(float AxisValue)
{
	AddMovementInput(FVector(AxisValue,0,0));
}

void AGemstoneCharacter::GuardMove()
{
	if(GetCharacterMovement()->Velocity.IsZero())
	{
		GetSprite()->SetFlipbook(Idel_PFb);
	}
	else
	{
		GetSprite()->SetFlipbook(Run_PFb);
	}
}
