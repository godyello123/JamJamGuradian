// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_DeathKnight.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_DeathKnight.h"
#include "../../NormalActor/DemonGate.h"

AMonster_DeathKnight::AMonster_DeathKnight()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/BlackKnight/BlackKnightSK.BlackKnightSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_DeathKnight, AnimAsset, "AnimBlueprint'/Game/02Monster/03DeathKnight/DeathKnight_Anim.DeathKnight_Anim_C'");

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


void AMonster_DeathKnight::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
}

bool AMonster_DeathKnight::IsDie()
{
    return bDie;
}

void AMonster_DeathKnight::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_DeathKnight>(GetMesh()->GetAnimInstance());
}

void AMonster_DeathKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster_DeathKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_DeathKnight::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_DeathKnight::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_DeathKnight::Attack()
{
}

void AMonster_DeathKnight::Move()
{
	
}

void AMonster_DeathKnight::Skill()
{
}

bool AMonster_DeathKnight::CheckTargetDistance()
{
	return false;
}
