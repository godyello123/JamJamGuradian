// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_RatAssassin.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_RatAssassin.h"
#include "../../NormalActor/DemonGate.h"

AMonster_RatAssassin::AMonster_RatAssassin()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/RatAssassin/RatAssassinSK.RatAssassinSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_RatAssassin, AnimAsset, "AnimBlueprint'/Game/02Monster/08RatAssassin/Rat_Anim.Rat_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bDie = false;

	fMPRecovery = 0;
	fDistance = 1000.f;
	SetMonsterState(5, 5, 5, 100, 100);
}

void AMonster_RatAssassin::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
}

bool AMonster_RatAssassin::IsDie()
{
	return bDie;
}

void AMonster_RatAssassin::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_RatAssassin>(GetMesh()->GetAnimInstance());
}

void AMonster_RatAssassin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster_RatAssassin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_RatAssassin::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	State.iHP -= DamageAmount;
	if (State.iHP <= 0)
	{
		//Á×ÀÌ±â
		if (Animation)
		{
			Die();
		}
	}

	return State.iHP;

   
}

void AMonster_RatAssassin::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
	{
		Animation->ChangeAnimType(eType);
	}
}

void AMonster_RatAssassin::Attack()
{
}

void AMonster_RatAssassin::Move()
{
}

void AMonster_RatAssassin::Skill()
{
}

bool AMonster_RatAssassin::CheckTargetDistance()
{	
	return false;
}
