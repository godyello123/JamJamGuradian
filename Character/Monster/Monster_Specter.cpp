// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Specter.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_Specter.h"
#include "../../NormalActor/DemonGate.h"

AMonster_Specter::AMonster_Specter()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/Specter/SpecterSK.SpecterSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Specter, AnimAsset, "AnimBlueprint'/Game/02Monster/09Specter/Specter_Anim.Specter_Anim_C'");

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

void AMonster_Specter::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
}

bool AMonster_Specter::IsDie()
{
	return bDie;
}

void AMonster_Specter::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Specter>(GetMesh()->GetAnimInstance());
}

void AMonster_Specter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AMonster_Specter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

float AMonster_Specter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_Specter::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
	{
		Animation->ChangeAnimType(eType);
	}
}

void AMonster_Specter::Skill()
{
}

