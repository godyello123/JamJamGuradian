// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_DeathWorm.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_DeathWorm.h"
#include "../../NormalActor/DemonGate.h"


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
	bDie = true;
}

bool AMonster_DeathWorm::IsDie()
{
	return bDie;
}

void AMonster_DeathWorm::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_DeathWorm>(GetMesh()->GetAnimInstance());
}

void AMonster_DeathWorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster_DeathWorm::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_DeathWorm::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_DeathWorm::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
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
