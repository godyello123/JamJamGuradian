// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Warrior.h"
#include "Summoner.h"
#include "../../Animation/Guardian/Anim_Warrior.h"

AGuardian_Warrior::AGuardian_Warrior()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/DarkKnightSK.DarkKnightSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Warrior, AnimData, "AnimBlueprint'/Game/01Guardian/05Warrior/Warrior_Anim.Warrior_Anim_C'");

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

void AGuardian_Warrior::AttackEnable(bool bEnable)
{
}

bool AGuardian_Warrior::IsAttack() const
{
	return false;
}

void AGuardian_Warrior::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Warrior::BeginPlay()
{
	Super::BeginPlay();
}

void AGuardian_Warrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGuardian_Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Warrior::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AGuardian_Warrior::Attack()
{
}

void AGuardian_Warrior::SearchTarget()
{
}

void AGuardian_Warrior::CheckDistance()
{
}

void AGuardian_Warrior::AttackToTarget()
{
}
