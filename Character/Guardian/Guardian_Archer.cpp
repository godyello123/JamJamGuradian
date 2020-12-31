// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Archer.h"
#include "Summoner.h"
#include "../../Animation/Guardian/Anim_Archer.h"



AGuardian_Archer::AGuardian_Archer()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/ApprenticeSK.ApprenticeSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Archer, AnimData, "AnimBlueprint'/Game/01Guardian/02Archer/Archer_Anim.Archer_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	SetState(10, 10, 10, 1.f);

	fAttackDist = 200.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;
	Target = nullptr;
	bAttack = false;
	bTarget = false;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}


void AGuardian_Archer::AttackEnable(bool bEnable)
{
}

bool AGuardian_Archer::IsAttack() const
{
	return false;
}

void AGuardian_Archer::LevelUP(ELevelUpType eType)
{
	switch (eType)
	{
	case ELevelUpType::TYPE1:
		break;
	case ELevelUpType::TYPE2:
		break;
	case ELevelUpType::TYPE3:
		break;
	case ELevelUpType::TYPE4:
		break;
	}
}


void AGuardian_Archer::BeginPlay()
{
	Super::BeginPlay();
}

void AGuardian_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGuardian_Archer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Archer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void AGuardian_Archer::Attack()
{
}

void AGuardian_Archer::SearchTarget()
{
}

void AGuardian_Archer::CheckDistance()
{
}

void AGuardian_Archer::AttackToTarget()
{
}