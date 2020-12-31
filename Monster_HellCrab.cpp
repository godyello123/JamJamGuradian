// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_HellCrab.h"
#include "Anim_HellCrab.h"
#include "AIController.h"


AMonster_HellCrab::AMonster_HellCrab()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/CrabMonster/CrabMonsterSK.CrabMonsterSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_HellCrab, AnimAsset, "AnimBlueprint'/Game/02Monster/06HellCrab/HellCrab_Anim.HellCrab_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bDie = false;

	fMPRecovery = 0;
	fDistance = 1000.f;
	SetMonsterState(5, 5, 5, 100, 100);

}


void AMonster_HellCrab::Die()
{
	bDie = true;
}

bool AMonster_HellCrab::IsDie()
{
	return bDie;
}

void AMonster_HellCrab::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster_HellCrab::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster_HellCrab::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_HellCrab::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AMonster_HellCrab::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
	{

	}
		
}

void AMonster_HellCrab::Attack()
{
}

void AMonster_HellCrab::Move()
{
}

void AMonster_HellCrab::Skill()
{
}

bool AMonster_HellCrab::CheckTargetDistance()
{
	return false;
}
