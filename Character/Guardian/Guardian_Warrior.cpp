// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Warrior.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Warrior.h"

AGuardian_Warrior::AGuardian_Warrior()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/SoldierSK.SoldierSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Warrior, AnimData, "AnimBlueprint'/Game/01Guardian/05Warrior/Warrior_Anim.Warrior_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	SetState(5, 10, 10, 1.f);

	fAttackDist = 200.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;
	Target = nullptr;
	bAttack = false;
	bTarget = false;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	TwoHandSword = nullptr;
}


void AGuardian_Warrior::Groggy()
{
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Warrior::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

void AGuardian_Warrior::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Warrior::BeginPlay()
{
	Super::BeginPlay();


	Animation = Cast<UAnim_Warrior>(GetMesh()->GetAnimInstance());

	LoadTwohandSword(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Sword01SM.Sword01SM'"));
	//TwoHandSword->SetActorRelativeLocation(FVector(0.f, 10.f, 0.363824));
	TwoHandSword->SetActorRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
}

void AGuardian_Warrior::SetAI(EWARRIOR_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Warrior::LoadTwohandSword(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TwoHandSword = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	TwoHandSword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	TwoHandSword->LoadMesh(strMeshPath);
}

void AGuardian_Warrior::ChangeAnimation(EGuardianAnimType eType)
{
	if (IsValid(Animation))
	{
		Animation->ChangeAnimType(eType);
	}
}

void AGuardian_Warrior::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 

	Motion();
}

void AGuardian_Warrior::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Warrior::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void AGuardian_Warrior::Motion()
{
	switch (eAI)
	{
	case EWARRIOR_AI::Idle:
		SearchTarget();
		break;
	case EWARRIOR_AI::Attack:
		CheckDistance();
		break;
	case EWARRIOR_AI::Groggy:
		Groggy();
		break;
	case EWARRIOR_AI::Victory:
		Victory();
		break;
	}
}

void AGuardian_Warrior::Attack()
{
	//if (State.iMP >= State.iMPMax)
	//	ChangeAnimation(EGuardianAnimType::GAT_Skill);
	//else
	//	ChangeAnimation(EGuardianAnimType::GAT_Attack);

	ChangeAnimation(EGuardianAnimType::GAT_Attack);
}

void AGuardian_Warrior::Skill()
{
}

void AGuardian_Warrior::SearchTarget()
{
	if (Target || bTarget)
		return;

	Animation->ChangeAnimType(EGuardianAnimType::GAT_Idle);

	FVector StartLoc = GetActorLocation();

	FVector TargetLoc = FVector(StartLoc.X + fAttackDist, StartLoc.Y + fAttackDist, StartLoc.Z + fAttackDist);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> HitRetArray;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), StartLoc, StartLoc, fAttackDist, TEXT("BlockAll"), false, IgnoreActors,
		EDrawDebugTrace::Type::None, HitRetArray, true);

	if (isHit)
	{
		int32 iSize = HitRetArray.Num();

		for (int32 i = 0; i < iSize; ++i)
		{
			if (HitRetArray[i].Component.Get()->GetCollisionProfileName() == FName(TEXT("Monster")))
			{
				AActor* pTarget = HitRetArray[i].Actor.Get();

				AMonster* Mon = (AMonster*)pTarget;

				if (!Mon->IsDead())
				{
					Target = pTarget;
					bTarget = true;
					eAI = EWARRIOR_AI::Attack;
				}

				return;
			}
		}
	}
}

bool AGuardian_Warrior::CheckDistance()
{
	if (Target && bTarget)
	{
		FVector TargetLoc = Target->GetActorLocation();
		TargetLoc.Z = 0.f;
		FVector MyLoc = GetActorLocation();
		MyLoc.Z = 0.f;

		FVector vDir = TargetLoc - MyLoc;
		vDir.Normalize();

		SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

		Attack();

		return true;
	}
	else
	{
		eAI = EWARRIOR_AI::Idle;
		return false;
	}

	return false;
}

void AGuardian_Warrior::AttackToTarget()
{
	if (bTarget && Target)
	{
		AController* AI = GetController<AController>();

		FDamageEvent DmgEvent;

		float fHp = Target->TakeDamage(State.Damage, DmgEvent, AI, this);

		FVector TargetLoc = Target->GetActorLocation();
		TargetLoc.Z = 0.f;
		FVector MyLoc = GetActorLocation();

		float fDist = FVector::Distance(TargetLoc, MyLoc);

		if (fDist > fAttackDist)
		{
			Target = nullptr;
			bTarget = false;
			//bAttack = false;
			eAI = EWARRIOR_AI::Idle;
		}
		else
		{
			bTarget = true;
		}

		if (fHp <= 0.f)
		{
			Target = nullptr;
			bTarget = false;
		}
	}
}

void AGuardian_Warrior::CrushAttack()
{

}

