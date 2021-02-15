// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Ranger.h"
#include "../../Animation/Guardian/Anim_Ranger.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Hunter.h"
#include "../../Controller/SummonerController.h"
#include "../../GameMode/DefenstPlayerState.h"

AGuardian_Ranger::AGuardian_Ranger()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/EngineerSK.EngineerSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Ranger, AnimData, "AnimBlueprint'/Game/01Guardian/02Archer/Ranger_Anim.Ranger_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	/*GetClassAsset(ASpell_MultiShot, ArrowAsset, "Blueprint'/Game/05Spell/Multishot_BP.Multishot_BP_C'");

	if (ArrowAsset.Succeeded())
		Arrow = ArrowAsset.Class;*/

	SetState(2, 10, 1.5, 1.f);

	//fAttackDist = 400.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));

	Bow = nullptr;

	eAI = EGUARDIAN_AI::Idle;

	m_eElementalType = EElementalType::ET_Normal;
}

void AGuardian_Ranger::SetElemental(EElementalType eType)
{
	m_eElemental = eType;

	switch (m_eElemental)
	{
	case EElementalType::ET_Normal:
	{

	}
	break;
	case EElementalType::ET_Fire:
	{

	}
	break;
	case EElementalType::ET_Ice:
	{

	}
	break;
	}
}

void AGuardian_Ranger::SetAI(EGUARDIAN_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Ranger::LoadBow(const FString & strSocket, const FString & strMeshPath)
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

void AGuardian_Ranger::ChangeAnimation(EGuardianAnimType eType)
{
	if (IsValid(Animation))
		Animation->ChangeAnimType(eType);
}

void AGuardian_Ranger::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Ranger>(GetMesh()->GetAnimInstance());

	LoadBow(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Bow02SM.Bow02SM'"));

	SetFillMP(0.3);

	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();

	m_iDmgLevel = pState->GetNormalDmg();

	//State.AttackSpeed = m_iDmgLevel + (m_iDmgLevel * 1);
	State.Damage = State.Damage + (m_iDmgLevel * 5);
	Bow->SetActorRelativeScale3D(FVector(1.3f, 1.3f, 1.3f));
}

void AGuardian_Ranger::Tick(float DeltaTime)
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

void AGuardian_Ranger::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Ranger::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

void AGuardian_Ranger::Groggy()
{
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Ranger::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

void AGuardian_Ranger::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Ranger::NormalLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(LightningLevelUp_EffectAsset, vLoc, vRot);
}

void AGuardian_Ranger::FireLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(FireLevelUp_EffectAsset, vLoc, vRot);
}

void AGuardian_Ranger::IceLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(IceLevelUp_EffectAsset, vLoc, vRot);
}

void AGuardian_Ranger::Dead()
{
	Super::Dead();
	Bow->Destroy();
}

void AGuardian_Ranger::Motion()
{
	switch (eAI)
	{
	case EGUARDIAN_AI::Idle:
		SearchTarget();
		break;
	case EGUARDIAN_AI::Attack:
		CheckDistance();
		break;
	case EGUARDIAN_AI::Victory:
		Victory();
		break;
	case EGUARDIAN_AI::Groggy:
		Groggy();
		break;
	}
}

void AGuardian_Ranger::Attack()
{
	if (State.iMP >= State.iMPMax)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
}

void AGuardian_Ranger::Skill()
{
}

void AGuardian_Ranger::SearchTarget()
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

bool AGuardian_Ranger::CheckDistance()
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

void AGuardian_Ranger::AttackToTarget()
{
}

void AGuardian_Ranger::MultiShot()
{
}
