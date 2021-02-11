// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Beholder.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_Beholder.h"
#include "../../NormalActor/DemonGate.h"


AMonster_Beholder::AMonster_Beholder()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/Beholder/BeholderSK.BeholderSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Beholder, AnimAsset,"AnimBlueprint'/Game/02Monster/01Beholder/Beholder_Anim.Beholder_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SetMonsterState(5, 5, 5, 100, 1);
}

void AMonster_Beholder::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Beholder>(GetMesh()->GetAnimInstance());
}

void AMonster_Beholder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster_Beholder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_Beholder::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_Beholder::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_Beholder::Skill()
{
}

void AMonster_Beholder::Groggy()
{
	bGroggy = true;
	ChangeAnim(EMonsterAnimType::MAT_Groggy);
}
