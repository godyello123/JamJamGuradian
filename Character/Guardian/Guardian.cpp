// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian.h"
#include "Summoner.h"


// Sets default values
AGuardian::AGuardian()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Summoner = nullptr;

	bCritical = false;

	CriticalChance = 10;
	CriticalRatio = 1.5;
	MPFillTime = 0.f;
	MPFillTimeMax = 1.f;

	Target = nullptr;
	bTarget = false;

	fAttackDist = 3000.f;

	//SetActorType(EActorType::AT_Guardian);

	Tags.Add("Guardian");
}

AActor* AGuardian::GetTarget() const
{
	return Target;
}

void AGuardian::SetFillMP(float iFill)
{
	FillMP = iFill;
}

void AGuardian::SetState(int32 iDmg, int32 HP, int32 MP, float Speed)
{
	State.Damage = iDmg;
	State.iHPMax = HP;
	State.iHP = State.iHPMax;
	State.iMPMax = MP;
	State.iMP = 0;
	State.AttackSpeed = Speed;
}

FGuardianState AGuardian::GetState() const
{
	return State;
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

void AGuardian::FillUpMP(float iValue, float fTime)
{
	MPFillTime += fTime;

	if (MPFillTime >= MPFillTimeMax)
	{
		State.iMP += iValue;

		if (State.iMP >= State.iMPMax)
			State.iMP = State.iMPMax;
		MPFillTime = 0.f;
	}
}

void AGuardian::Motion()
{
}

void AGuardian::Attack()
{
}

void AGuardian::Skill()
{
}

void AGuardian::SearchTarget()
{
}

void AGuardian::ShowUI(bool bShow)
{

}

void AGuardian::AttackEnable(bool bEnable)
{
	bAttack = bEnable;
}

bool AGuardian::IsAttack() const
{
	return bAttack;
}

void AGuardian::Groggy()
{
}

void AGuardian::Victory()
{
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

	FillUpMP(FillMP, DeltaTime);
}

// Called to bind functionality to input
void AGuardian::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGuardian::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

