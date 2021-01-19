// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_ChestImp.h"
#include "AIController.h"
#include "../../NormalActor/DemonGate.h"
#include "../../Animation/Monster/Anim_ChestImp.h"


AMonster_ChestImp::AMonster_ChestImp()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/ChestMonster/ChestMonsterSK.ChestMonsterSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_ChestImp, AnimAsset, "AnimBlueprint'/Game/02Monster/02ChestImp/ChestImp_Anim.ChestImp_Anim_C'");

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

void AMonster_ChestImp::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
}

void AMonster_ChestImp::Attack()
{
	if (Target)
	{
		AController* Ai = GetController<AController>();
		FDamageEvent DmgEvent;
		Target->TakeDamage(State.Damage, DmgEvent, Ai, this);
	}
}

bool AMonster_ChestImp::IsDie()
{
	return bDie;
}

void AMonster_ChestImp::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_ChestImp>(GetMesh()->GetAnimInstance());
}

void AMonster_ChestImp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster_ChestImp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_ChestImp::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	State.iHP -= DamageAmount;
	if (State.iHP <= 0)
	{
		//���̱�
		if (Animation)
		{
			Die();
		}
	}

	return State.iHP;
}

void AMonster_ChestImp::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_ChestImp::Move()
{

}

void AMonster_ChestImp::Skill()
{
}

bool AMonster_ChestImp::CheckTargetDistance()
{

	return false;
}


