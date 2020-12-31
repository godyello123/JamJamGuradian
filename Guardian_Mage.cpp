// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Mage.h"
#include "Anim_Mage.h"
#include "Summoner.h"

AGuardian_Mage::AGuardian_Mage()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/MageSK.MageSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Mage, AnimData, "AnimBlueprint'/Game/01Guardian/04Mage/Mage_Anim.Mage_Anim_C'");

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

void AGuardian_Mage::AttackEnable(bool bEnable)
{
}

bool AGuardian_Mage::IsAttack() const
{
	return false;
}

void AGuardian_Mage::LevelUP(ELevelUpType eType)
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

void AGuardian_Mage::BeginPlay()
{
	Super::BeginPlay();
}

void AGuardian_Mage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGuardian_Mage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Mage::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void AGuardian_Mage::Attack()
{
}

void AGuardian_Mage::SearchTarget()
{
}

void AGuardian_Mage::CheckDistance()
{
}

void AGuardian_Mage::AttackToTarget()
{
}
