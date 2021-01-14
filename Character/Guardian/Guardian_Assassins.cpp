// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Assassins.h"
#include "Summoner.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Assassins.h"

AGuardian_Assassins::AGuardian_Assassins()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/ShinobiSK.ShinobiSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Assassins, AnimData, "AnimBlueprint'/Game/01Guardian/03Assassin/Assassin_Anim.Assassin_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	SetState(10, 10, 10, 1.f);

	fAttackDist = 200.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;
	Target = nullptr;
	bAttack = false;
	bTarget = false;

	LeftDagger = nullptr;
	RightDagger = nullptr;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void AGuardian_Assassins::Groggy()
{
}

void AGuardian_Assassins::Victory()
{
}

void AGuardian_Assassins::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Assassins::SetAI(EASSASSIN_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Assassins::LoadRightDagger(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	RightDagger = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	RightDagger->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	RightDagger->LoadMesh(strMeshPath);
}

void AGuardian_Assassins::LoadLeftDagger(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	LeftDagger = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	LeftDagger->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	LeftDagger->LoadMesh(strMeshPath);
}

void AGuardian_Assassins::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Assassins>(GetMesh()->GetAnimInstance());

	//LoadRightDagger(TEXT(""), TEXT(""));
	//LoadLeftDagger(TEXT(""), TEXT(""));

}

void AGuardian_Assassins::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGuardian_Assassins::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Assassins::TakeDamage
(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}


void AGuardian_Assassins::Motion()
{
}

void AGuardian_Assassins::Attack()
{
}

void AGuardian_Assassins::Skill()
{
}

void AGuardian_Assassins::SearchTarget()
{
}

bool AGuardian_Assassins::CheckDistance()
{
	return false;
}

void AGuardian_Assassins::AttackToTarget()
{
}
