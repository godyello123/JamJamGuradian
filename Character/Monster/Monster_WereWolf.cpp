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


	SetMonsterState(5, 5, 5, 100, 0.8f);
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
		State.iHP = 0;
		//Á×ÀÌ±â
		if (Animation)
		{
			Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
			Dead();
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

