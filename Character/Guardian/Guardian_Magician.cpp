// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Magician.h"
#include "Summoner.h"
#include "Guardian_Mage.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Magician.h"
#include "../../Controller/SummonerController.h"
#include "../../GameMode/DefenstPlayerState.h"

AGuardian_Magician::AGuardian_Magician()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/MageSK.MageSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Magician, AnimData, "AnimBlueprint'/Game/01Guardian/04Mage/Magician_Anim.Magician_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	GetClassAsset(ASpell_MagicMissile, SpellAsset, "Blueprint'/Game/05Spell/MagicMissile_BP.MagicMissile_BP_C'");

	if (SpellAsset.Succeeded())
		MagicMissile = SpellAsset.Class;

	SetState(5, 10, 1, 1.f);

	//fAttackDist = 300.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	bAttack = false;

	SetFillMP(0.64);


	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Wand = nullptr;

	eAI = EGUARDIAN_AI::Idle;
}


void AGuardian_Magician::NormalLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(LightningLevelUp_EffectAsset, vLoc, vRot);
	AGuardian_Mage* pMage = GetWorld()->SpawnActor<AGuardian_Mage>(vLoc, vRot);
}

void AGuardian_Magician::FireLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(FireLevelUp_EffectAsset, vLoc, vRot);
	AGuardian_Mage* pMage = GetWorld()->SpawnActor<AGuardian_Mage>(vLoc, vRot);
}

void AGuardian_Magician::IceLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(IceLevelUp_EffectAsset, vLoc, vRot);
	AGuardian_Mage* pMage = GetWorld()->SpawnActor<AGuardian_Mage>(vLoc, vRot);
}

void AGuardian_Magician::Dead()
{
	Super::Dead();
	Wand->Destroy();
}

void AGuardian_Magician::BeginPlay()
{
	Super::BeginPlay();

	LoadWand(TEXT("weaponShield_r"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Wand01SM.Wand01SM'"));

	Animation = Cast<UAnim_Magician>(GetMesh()->GetAnimInstance());

	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();

	m_iDmgLevel = pState->GetNormalDmg();

	//State.AttackSpeed = m_iDmgLevel + (m_iDmgLevel * 1);
	State.Damage = State.Damage + (m_iDmgLevel * 5);
}

void AGuardian_Magician::SetAI(EGUARDIAN_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Magician::LoadWand(const FString& strSocket, const FString& strMeshPath)
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

void AGuardian_Magician::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_bDead)
	{
		Motion();
	}
	else
	{
		m_fDeadTime += DeltaTime;

		if (m_fDeadTime >= 6.f)
			this->Destroy();
	}
}

void AGuardian_Magician::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Magician::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}


void AGuardian_Magician::Attack()
{
	if (State.iMP >= State.iMPMax)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
	//else
	//	ChangeAnimation(EGuardianAnimType::GAT_Attack);

	//ChangeAnimation(EGuardianAnimType::GAT_Attack);
}

void AGuardian_Magician::Groggy()
{
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Magician::Skill()
{
	MagicMissaile();
}

void AGuardian_Magician::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

void AGuardian_Magician::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Magician::SearchTarget()
{
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

					eAI = EGUARDIAN_AI::Attack;
				}

				return;
			}
		}
	}
}

bool AGuardian_Magician::CheckDistance()
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
	}
	else
	{
		eAI = EGUARDIAN_AI::Idle;
		return false;
	}

	return false;
}

void AGuardian_Magician::AttackToTarget()
{
	if (bTarget&&Target)
	{
		AController* AI = GetController<AController>();

		FDamageEvent DmgEvent;

		float fHp = Target->TakeDamage(State.Damage, DmgEvent, AI, this);

		if (fHp <= 0.f)
		{
			Target = nullptr;
			bTarget = false;
		}
	}
}

void AGuardian_Magician::MagicMissaile()
{
	//스킬 만들기
	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;
	ASpell_MagicMissile* pMagic = GetWorld()->SpawnActor<ASpell_MagicMissile>(MagicMissile, vPos, GetActorRotation(),
		tParams);

	//pMagic->SetMage(this);

	State.iMP = 0.f;
}

void AGuardian_Magician::EraseTarget()
{
	Target = nullptr;
	bTarget = false;
}

void AGuardian_Magician::ChangeAnimation(EGuardianAnimType eType)
{
	if (IsValid(Animation))
	{
		Animation->ChangeAnimType(eType);
	}
}

void AGuardian_Magician::Motion()
{
	switch (eAI)
	{
	case EGUARDIAN_AI::Idle:
		SearchTarget();
		break;
	case EGUARDIAN_AI::Attack:
		CheckDistance();
		break;
	case EGUARDIAN_AI::Groggy:
		Groggy();
		break;
	case EGUARDIAN_AI::Victory:
		Victory();
		break;
	}
}

