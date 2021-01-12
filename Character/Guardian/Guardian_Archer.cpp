// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Archer.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Archer.h"



AGuardian_Archer::AGuardian_Archer()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/ApprenticeSK.ApprenticeSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Archer, AnimData, "AnimBlueprint'/Game/01Guardian/02Archer/Archer_Anim.Archer_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	SetState(10, 10, 10, 1.f);

	fAttackDist = 200.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;
	Target = nullptr;
	bTarget = false;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Bow = nullptr;
}

void AGuardian_Archer::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(Animation))
		Animation = Cast<UAnim_Archer>(GetMesh()->GetAnimInstance());

	LoadBow(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Bow01SM.Bow01SM'"));
}

void AGuardian_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGuardian_Archer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Archer::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AGuardian_Archer::Groggy()
{
}

void AGuardian_Archer::Victory()
{
}

void AGuardian_Archer::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Archer::Motion()
{
}

void AGuardian_Archer::Attack()
{
}

void AGuardian_Archer::Skill()
{
}

void AGuardian_Archer::SearchTarget()
{
}

bool AGuardian_Archer::CheckDistance()
{
	return false;
}

void AGuardian_Archer::AttackToTarget()
{
}

void AGuardian_Archer::SetAI(EARCHER_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Archer::LoadBow(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	Bow = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	Bow->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	Bow->LoadMesh(strMeshPath);
}
