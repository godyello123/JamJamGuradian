// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "../../NormalActor/DemonGate.h"
#include "AIController.h"


// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;
	bDead = false;

	Tags.Add("Monster");
}

bool AMonster::IsDead()
{
	if (State.iHP > 0)
		return false;
	else
		return true;
}

void AMonster::Dead()
{
	bDead = true;
}

void AMonster::SetTarget(AActor* pTarget)
{
	Target = pTarget;
}

void AMonster::SetDemonGate(ADemonGate* pGate)
{
	if(IsValid(pGate))
		Gate = pGate;
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMonster::ChangeAnim(EMonsterAnimType eType)
{

}

void AMonster::SetMonsterState(int32 iDamage, int32 iHP, int32 iMP, float fATSpeed, float fMoveSpeed)
{
	State.Damage = iDamage;
	State.iHPMax = iHP;
	State.iHP = State.iHPMax;
	State.iMPMax = iMP;
	State.iMP = 0;
	State.MoveSpeed = fMoveSpeed;
	State.AttackSpeed = fATSpeed;
}


