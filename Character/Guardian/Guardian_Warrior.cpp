// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Warrior.h"
#include "Summoner.h"
#include "../../Animation/Guardian/Anim_Warrior.h"

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
}

void AGuardian_Warrior::Tick(float DeltaTime)
{
}

void AGuardian_Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
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
