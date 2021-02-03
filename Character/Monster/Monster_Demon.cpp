// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Demon.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_Demon.h"
#include "../../NormalActor/DemonGate.h"


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

	SetMonsterState(10, 10, 10, 100, 1.5);
}

void AMonster_Demon::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Demon>(GetMesh()->GetAnimInstance());

}

void AMonster_Demon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonster_Demon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_Demon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_Demon::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_Demon::Skill()
{

}