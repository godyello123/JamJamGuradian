// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Archer.h"
#include "Summoner.h"

AGuardian_Archer::AGuardian_Archer()
{
	TICKON;
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
