// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Mage.h"
#include "Summoner.h"

AGuardian_Mage::AGuardian_Mage()
{
	TICKON;
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