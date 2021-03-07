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


}


void AMonster_RatAssassin::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_RatAssassin>(GetMesh()->GetAnimInstance());

	SetMonsterState(5, 5, 5, 100, 1.f);
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

void AMonster_RatAssassin::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
	{
		Animation->ChangeAnimType(eType);
	}
}

void AMonster_RatAssassin::Skill()
{
}

void AMonster_RatAssassin::Groggy()
{
	bGroggy = true;
	ChangeAnim(EMonsterAnimType::MAT_Groggy);
}

