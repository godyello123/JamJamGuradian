// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Hunter.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Hunter.h"
#include "../../Controller/SummonerController.h"
#include "../../GameMode/DefenstPlayerState.h"

AGuardian_Hunter::AGuardian_Hunter()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/CountSK.CountSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Archer, AnimData, "AnimBlueprint'/Game/01Guardian/02Archer/Archer_Anim.Archer_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	GetClassAsset(ASpell_MultiShot, ArrowAsset, "Blueprint'/Game/05Spell/Multishot_BP.Multishot_BP_C'");

	if (ArrowAsset.Succeeded())
		Arrow = ArrowAsset.Class;

	SetState(2, 10, 10, 1.f);

	//fAttackDist = 400.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Bow = nullptr;

	eAI = EHUNTER_AI::Idle;

	m_eElementalType = EElementalType::ET_Normal;
}

void AGuardian_Hunter::SetElemental(EElementalType eType)
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

void AGuardian_Hunter::SetAI(EHUNTER_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Hunter::LoadBow(const FString & strSocket, const FString & strMeshPath)
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

void AGuardian_Hunter::ChangeAnimation(EGuardianAnimType eType)
{
	if (IsValid(Animation))
		Animation->ChangeAnimType(eType);
}

void AGuardian_Hunter::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Hunter>(GetMesh()->GetAnimInstance());

	LoadBow(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Bow01SM.Bow01SM'"));

	SetFillMP(0.3);

	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();

	m_iDmgLevel = pState->GetNormalDmg();

	//State.AttackSpeed = m_iDmgLevel + (m_iDmgLevel * 1);
	State.Damage = State.Damage + (m_iDmgLevel * 5);
}

void AGuardian_Hunter::Tick(float DeltaTime)
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

void AGuardian_Hunter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Hunter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	return 0.0f;
}

void AGuardian_Hunter::Groggy()
{
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Hunter::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

void AGuardian_Hunter::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Hunter::NormalLevelUp()
{
}

void AGuardian_Hunter::FireLevelUp()
{
}

void AGuardian_Hunter::IceLevelUp()
{
}

void AGuardian_Hunter::Motion()
{
	switch (eAI)
	{
	case EHUNTER_AI::Idle:
		SearchTarget();
		break;
	case EHUNTER_AI::Attack:
		CheckDistance();
		break;
	case EHUNTER_AI::Victory:
		Victory();
		break;
	case EHUNTER_AI::Groggy:
		Groggy();
		break;
	}
}

void AGuardian_Hunter::Attack()
{
	if (State.iMP >= State.iMPMax)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
	else
		ChangeAnimation(EGuardianAnimType::GAT_Attack);

}

void AGuardian_Hunter::Skill()
{
}

void AGuardian_Hunter::SearchTarget()
{
	if (Target || bTarget)
	{
		eAI = EHUNTER_AI::Attack;
		return;
	}

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

					eAI = EHUNTER_AI::Attack;
				}

				return;
			}
		}
	}
}

bool AGuardian_Hunter::CheckDistance()
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
		eAI = EHUNTER_AI::Idle;
		return false;
	}

	return false;
}

void AGuardian_Hunter::AttackToTarget()
{
	if (bTarget&&Target)
	{
		AController* AI = GetController<AController>();

		FDamageEvent DmgEvent;

		//속성 별로 특성 추가 해주기

		float fHp = Target->TakeDamage(State.Damage, DmgEvent, AI, this);

		if (fHp <= 0.f)
		{
			Target = nullptr;
			bTarget = false;
		}
	}
}

void AGuardian_Hunter::MultiShot()
{
	for (int32 i = -2; i < 3; ++i)
	{
		FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

		FRotator vRot = GetActorRotation();

		vRot.Yaw += i * 5.f;

		FActorSpawnParameters tParams;

		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		tParams.Owner = this;

		ASpell_MultiShot* pArrow = GetWorld()->SpawnActor<ASpell_MultiShot>(Arrow, vPos, vRot,
			tParams);
		//속성 별로 파티클 다른거 넣어주기
	}

	State.iMP = 0;
}
