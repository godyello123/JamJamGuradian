// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Mage.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Mage.h"

AGuardian_Mage::AGuardian_Mage()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/WizardSK.WizardSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Mage, AnimData, "AnimBlueprint'/Game/01Guardian/04Mage/Mage_Anim.Mage_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	GetClassAsset(ASpell_MagicMissile, SpellAsset, "Blueprint'/Game/05Spell/MagicMissile_BP.MagicMissile_BP_C'");

	if (SpellAsset.Succeeded())
		MagicMissile = SpellAsset.Class;

	SetState(10, 10, 10, 1.f);

	fAttackDist = 300.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;
	Target = nullptr;
	bAttack = false;
	bTarget = false;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Wand = nullptr;

	eAI = EMAGE_AI::Idle;
}

void AGuardian_Mage::LevelUP(ELevelUpType eType)
{
	switch (eType)
	{
	case ELevelUpType::TYPE1:
		break;
	case ELevelUpType::TYPE2:
		break;
	case ELevelUpType::TYPE3:
break;
	case ELevelUpType::TYPE4:
		break;
	}
}

void AGuardian_Mage::BeginPlay()
{
	Super::BeginPlay();

	LoadWand(TEXT("weaponShield_r"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Wand01SM.Wand01SM'"));

	Animation = Cast<UAnim_Mage>(GetMesh()->GetAnimInstance());
}

void AGuardian_Mage::SetAI(EMAGE_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Mage::LoadWand(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::Undefined;

	Wand = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	Wand->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	Wand->LoadMesh(strMeshPath);
}

void AGuardian_Mage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Motion();
}

void AGuardian_Mage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Mage::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}


void AGuardian_Mage::Attack()
{
	if (State.iMP >= State.iMPMax)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
	else
		ChangeAnimation(EGuardianAnimType::GAT_Attack);
}

void AGuardian_Mage::Groggy()
{
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Mage::Skill()
{
	
}

void AGuardian_Mage::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

void AGuardian_Mage::SearchTarget()
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
					eAI = EMAGE_AI::Attack;
				}

				return;
			}
		}
	}
}

bool AGuardian_Mage::CheckDistance()
{
	FVector TargetLoc = Target->GetActorLocation();
	TargetLoc.Z = 0.f;
	FVector MyLoc = GetActorLocation();
	MyLoc.Z = 0.f;

	float fDist = FVector::Distance(TargetLoc, MyLoc);

	if (fDist > fAttackDist)
	{
		Target = nullptr;
		bTarget = false;
		eAI = EMAGE_AI::Idle;

		return false;
	}
	else
	{
		if (bAttack)
			return false;

		bTarget = true;

		FVector vDir = TargetLoc - MyLoc;
		vDir.Normalize();
		SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

		Attack();

		return true;
	}

	return false;
}

void AGuardian_Mage::AttackToTarget()
{

}

void AGuardian_Mage::MagicMissaile()
{
	//스킬 만들기
	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;


	ASpell_MagicMissile* pMagic= GetWorld()->SpawnActor<ASpell_MagicMissile>(MagicMissile, vPos, GetActorRotation(),
		tParams);

	pMagic->SetMage(this);
}

void AGuardian_Mage::ChangeAnimation(EGuardianAnimType eType)
{
	if (IsValid(Animation))
	{
		Animation->ChangeAnimType(eType);
	}
}

void AGuardian_Mage::Motion()
{
	switch (eAI)
	{
	case EMAGE_AI::Idle:
		SearchTarget();
		break;
	case EMAGE_AI::Attack:
		CheckDistance();
		break;
	case EMAGE_AI::Groggy:
		Groggy();
		break;
	case EMAGE_AI::Victory:
		Victory();
		break;
	}
}

