// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_LizardMan.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_Lizardman.h"
#include "../../NormalActor/DemonGate.h"

AMonster_LizardMan::AMonster_LizardMan()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/LizardWarrior/LizardWarriorSK.LizardWarriorSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Lizardman, AnimAsset, "AnimBlueprint'/Game/02Monster/07Lizardman/LizardMan_Anim.LizardMan_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SetMonsterState(5, 5, 5, 100, 1.f);
}

void AMonster_LizardMan::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Lizardman>(GetMesh()->GetAnimInstance());
}

void AMonster_LizardMan::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMonster_LizardMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_LizardMan::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_LizardMan::ChangeAnim(EMonsterAnimType eType)
{
    if (Animation)
	{
		Animation->ChangeAnimType(eType);
    }
     
}

void AMonster_LizardMan::Skill()
{
}

void AMonster_LizardMan::Groggy()
{
	bGroggy = true;
	ChangeAnim(EMonsterAnimType::MAT_Groggy);
}

