// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian.h"
#include "Summoner.h"


// Sets default values
AGuardian::AGuardian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Summoner = nullptr;

	bCritical = false;

	CriticalChance = 10;
	CriticalRatio = 1.5;

	DetectTime = 0.f;
	DetectTimeMax = 0.5f;
}

void AGuardian::SetState(int32 iDmg, int32 HP, int32 MP, float Speed)
{
	State.Damage = iDmg;
	State.iHPMax = HP;
	State.iHP = State.iHPMax;
	State.iMPMax = MP;
	State.iMP = State.iMPMax;
	State.AttackSpeed = Speed;
}

void AGuardian::SetCriticalChance(int32 iChance)
{
	CriticalChance = iChance;
}

void AGuardian::SetCriticalRatio(float fRatio)
{
	CriticalRatio = fRatio;
}

int32 AGuardian::GetCriticalChance() const
{
	return CriticalChance;
}

float AGuardian::GetCriticalRatio() const
{
	return CriticalRatio;
}

void AGuardian::AddCriticalChance()
{
	++CriticalChance;
}

void AGuardian::AddCriticalRatio()
{
	++CriticalRatio;
}

void AGuardian::SetSummoner(ASummoner* Sum)
{
	Summoner = Sum;
}

bool AGuardian::IsSummoner()
{
	if (IsValid(Summoner))
		return true;
	
	return false;
}

void AGuardian::LevelUP(ELevelUpType eType)
{

}

// Called when the game starts or when spawned
void AGuardian::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGuardian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AGuardian::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

