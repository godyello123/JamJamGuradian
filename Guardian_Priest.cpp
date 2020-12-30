// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Priest.h"
#include "Summoner.h"

AGuardian_Priest::AGuardian_Priest()
{
	TICKON;
}

void AGuardian_Priest::LevelUP(ELevelUpType eType)
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

void AGuardian_Priest::BeginPlay()
{
	Super::BeginPlay();
}

void AGuardian_Priest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGuardian_Priest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Priest::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}