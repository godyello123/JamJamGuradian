// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_DeathWorm.h"
#include "Anim_DeathWorm.h"
#include "AIController.h"


AMonster_DeathWorm::AMonster_DeathWorm()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/WormMonster/WormMonsterSK.WormMonsterSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_DeathWorm, AnimAsset, "AnimBlueprint'/Game/02Monster/04DeathWorm/DeathWorm_Anim.DeathWorm_Anim_C'");

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

void AMonster_DeathWorm::Die()
{
}

bool AMonster_DeathWorm::IsDie()
{
	return false;
}

void AMonster_DeathWorm::BeginPlay()
{
}

void AMonster_DeathWorm::Tick(float DeltaTime)
{
}

void AMonster_DeathWorm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

float AMonster_DeathWorm::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMonster_DeathWorm::ChangeAnim(EMonsterAnimType eType)
{
}

void AMonster_DeathWorm::Attack()
{
}

void AMonster_DeathWorm::Move()
{
}

void AMonster_DeathWorm::Skill()
{
}

bool AMonster_DeathWorm::CheckTargetDistance()
{
	return false;
}
