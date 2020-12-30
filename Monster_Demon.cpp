// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Demon.h"
#include "Anim_Demon.h"
#include "AIController.h"


AMonster_Demon::AMonster_Demon()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/FlyingDemon/FlyingDemonSK.FlyingDemonSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Demon, AnimAsset, "AnimBlueprint'/Game/02Monster/05Demon/Demon_Anim.Demon_Anim_C'");

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

void AMonster_Demon::Die()
{
}

bool AMonster_Demon::IsDie()
{
    return false;
}

void AMonster_Demon::BeginPlay()
{
}

void AMonster_Demon::Tick(float DeltaTime)
{
}

void AMonster_Demon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

float AMonster_Demon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    return 0.0f;
}

void AMonster_Demon::ChangeAnim(EMonsterAnimType eType)
{
}

void AMonster_Demon::Attack()
{
}

void AMonster_Demon::Move()
{
}

void AMonster_Demon::Skill()
{
}

bool AMonster_Demon::CheckTargetDistance()
{
    return false;
}
