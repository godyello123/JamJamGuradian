// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_WereWolf.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_WereWolf.h"
#include "../../NormalActor/DemonGate.h"

AMonster_WereWolf::AMonster_WereWolf()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/Werewolf/WerewolfSK.WerewolfSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_WereWolf, AnimAsset, "AnimBlueprint'/Game/02Monster/10WereWolf/WereWolf_Anim.WereWolf_Anim_C'");

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
	SetMonsterState(5, 5, 5, 100, 1.f);
}

void AMonster_WereWolf::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);

}

bool AMonster_WereWolf::IsDie()
{
	return bDie;

}

void AMonster_WereWolf::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_WereWolf>(GetMesh()->GetAnimInstance());
}

void AMonster_WereWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster_WereWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

float AMonster_WereWolf::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_WereWolf::ChangeAnim(EMonsterAnimType eType)
{

	if (Animation)
	{
		Animation->ChangeAnimType(eType);
	}
}

void AMonster_WereWolf::Skill()
{
}

