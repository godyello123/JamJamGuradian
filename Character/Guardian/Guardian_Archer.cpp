// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Archer.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Archer.h"
#include "../../Controller/SummonerController.h"
#include "../../GameMode/DefenstPlayerState.h"




AGuardian_Archer::AGuardian_Archer()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/CountSK.CountSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Archer, AnimData, "AnimBlueprint'/Game/01Guardian/02Archer/Archer_Anim.Archer_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	GetClassAsset(ASpell_MultiShot, ArrowAssetred, "Blueprint'/Game/05Spell/Multishot_BP_Red.Multishot_BP_Red_C'");

	if (ArrowAssetred.Succeeded())
		Arrow_Red = ArrowAssetred.Class;

	GetClassAsset(ASpell_MultiShot, ArrowAssetblue, "Blueprint'/Game/05Spell/Multishot_BP1_Blue.Multishot_BP1_Blue_C'");

	if (ArrowAssetblue.Succeeded())
		Arrow_Blue = ArrowAssetblue.Class;

	GetClassAsset(ASpell_MultiShot, ArrowAssetYellow, "Blueprint'/Game/05Spell/Multishot_BP2_Yellow.Multishot_BP2_Yellow_C'");

	if (ArrowAssetYellow.Succeeded())
		Arrow_Yellow = ArrowAssetYellow.Class;

	GetClassAsset(ASpell_ExplosionArrow, ExArrowAsset, "Blueprint'/Game/05Spell/ExplosionArrow_BP.ExplosionArrow_BP_C'");

	if (ExArrowAsset.Succeeded())
		ExplosionArrow = ExArrowAsset.Class;

	GetClassAsset(ASpell_IceArrow, IceArrowAsset, "Blueprint'/Game/05Spell/IceArrow_BP.IceArrow_BP_C'");

	if (IceArrowAsset.Succeeded())
		IceArrow = IceArrowAsset.Class;

	GetClassAsset(ASpell_StaticArrow, StaticArrowAsset, "Blueprint'/Game/05Spell/StaticArrow_BP.StaticArrow_BP_C'");

	if (StaticArrowAsset.Succeeded())
		StaticArrow = StaticArrowAsset.Class;

	GetClassAsset(ASpell_RainofArrow, Rain, "Blueprint'/Game/05Spell/RainofArrow_BP.RainofArrow_BP_C'");

	if (Rain.Succeeded())
		RainOfArrow = Rain.Class;

	GetClassAsset(ASpell_CrystalArrow, Crystal, "Blueprint'/Game/05Spell/CrystalArrow_BP.CrystalArrow_BP_C'");

	if (Crystal.Succeeded())
		CrystalArrow = Crystal.Class;




	/*SetState(2, 10, 2, 1.f);*/

	//fAttackDist = 400.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Bow = nullptr;

	eAI = EGUARDIAN_AI::Idle;

	m_eElementalType = EElementalType::ET_Normal;
}

void AGuardian_Archer::BeginPlay()
{
	Super::BeginPlay();

	SetState(5, 1.f, 6.f, 10.f, 1.f);
	SetFillTierGage_1(0.5f);
	SetFillTierGage_2(0.f);
	SetFillTierGage_3(0.f);

	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();

	Animation = Cast<UAnim_Archer>(GetMesh()->GetAnimInstance());

	LoadBow(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Bow01SM.Bow01SM'"));

	m_iDmgLevel = pState->GetNormalDmg();

	State.iDamage = State.iDamage + (m_iDmgLevel * 5);

	m_bTire3Skill = false;
}

void AGuardian_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FillUpTierGage_1(m_fFillTierGage_1, DeltaTime);
	FillUpTierGage_2(m_fFillTierGage_2, DeltaTime);
	FillUpTierGage_3(m_fFillTierGage_3, DeltaTime);

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
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Archer::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

void AGuardian_Archer::LevelUp(EGUARDIANLEVEL eLevel, EElementalType eType)
{
	switch (eLevel)
	{
	case EGUARDIANLEVEL::GL_LEVEL1:
	{
		Archer_Tier2(eType);
	}
	break;
	case EGUARDIANLEVEL::GL_LEVEL2:
	{
		Archer_Tier3(eType);
	}
	break;
	case EGUARDIANLEVEL::GL_LEVEL3:
	{

	}
	break;
	}
}

void AGuardian_Archer::Dead()
{
	Super::Dead();
	Bow->Destroy();
}

void AGuardian_Archer::Motion()
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

void AGuardian_Archer::Attack()
{
	if (State.fTierGage_1 >= State.fTierGageMax_1 ||
		State.fTierGage_2 >= State.fTierGageMax_2 ||
		State.fTierGage_3 >= State.fTierGageMax_3)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
}

void AGuardian_Archer::Skill()
{
	if (State.fTierGage_3 >= State.fTierGageMax_3)
	{
		Tier3Skill();
		//State.fTierGage_3 = 0.f;
	}

	if (State.fTierGage_2 >= State.fTierGageMax_2)
	{
		Tier2Skill();
		State.fTierGage_2 = 0.f;
	}

	else if (State.fTierGage_1 >= State.fTierGageMax_1)
	{
		Shot();
	}
}

void AGuardian_Archer::SearchTarget()
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

void AGuardian_Archer::Targeting(const FVector& vLoc)
{
	PrintViewport(1.f, FColor::Yellow, TEXT("Archer tier3 skill"));

	if (m_bTire3Skill)
	{
		switch (m_eElementalType)
		{
		case EElementalType::ET_Normal:
			break;
		case EElementalType::ET_Fire:
			RainOfArrowSkill();
			break;
		case EElementalType::ET_Ice:
			break;
		}

		m_bTire3Skill = false;
		State.fTierGage_3 = 0.f;
	}
}

void AGuardian_Archer::Ultimate()
{

	State.fTierGage_3 = 0.f;

	switch (m_eElementalType)
	{
	case EElementalType::ET_Normal:
		MultiShot();
		break;
	case EElementalType::ET_Fire:
		RainOfArrowSkill();
		break;
	case EElementalType::ET_Ice:
		CrystalArrowSkill();
		break;
	}
}

void AGuardian_Archer::Archer_Tier2(EElementalType eType)
{
	USkeletalMesh* pMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/EngineerSK1.EngineerSK1'"));
	GetMesh()->SetSkeletalMesh(pMesh);
	GetMesh()->SetWorldScale3D(FVector(1.1f, 1.1f, 1.1f));
	SetGuardianLevel(EGUARDIANLEVEL::GL_LEVEL2);
	SetElementalType(eType);
	SetFillTierGage_2(0.5f);
}

void AGuardian_Archer::Archer_Tier3(EElementalType eType)
{
	USkeletalMesh* pMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/ImmortalSK.ImmortalSK'"));
	GetMesh()->SetSkeletalMesh(pMesh);
	GetMesh()->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	SetGuardianLevel(EGUARDIANLEVEL::GL_LEVEL3);
	SetElementalType(eType);
	SetFillTierGage_3(0.5f);
	HideUI();
	CreateDecal();
}

bool AGuardian_Archer::CheckDistance()
{
	if (Target && bTarget)
	{
		AMonster* pMon = Cast<AMonster>(Target);

		if (pMon->GetMonsterState().iHP <= 0)
		{
			Target = nullptr;
			bTarget = false;
			return false;
		}
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

void AGuardian_Archer::AttackToTarget()
{
	if (bTarget&&Target)
	{
		AController* AI = GetController<AController>();

		FDamageEvent DmgEvent;

		float fHp = Target->TakeDamage(State.iDamage, DmgEvent, AI, this);

		if (fHp <= 0.f)
		{
			Target = nullptr;
			bTarget = false;
		}
	}
}

void AGuardian_Archer::MultiShot()
{
	FVector TargetLoc = m_pDecal->GetActorLocation();
	TargetLoc.Z = 0.f;
	FVector MyLoc = GetActorLocation();
	MyLoc.Z = 0.f;

	FVector vDir = TargetLoc - MyLoc;
	vDir.Normalize();

	FRotator vRot = FRotator(0.f, vDir.Rotation().Yaw, 0.f);

	SetActorRotation(vRot);

	for (int32 i = -2; i < 3; ++i)
	{
		FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

		vRot.Yaw += i * 3.f;

		FActorSpawnParameters tParams;

		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		tParams.Owner = this;

		ASpell_StaticArrow* pArrow = GetWorld()->SpawnActor<ASpell_StaticArrow>(StaticArrow, vPos, vRot,
			tParams);
	}
}

void AGuardian_Archer::Shot()
{
	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

	FRotator vRot = GetActorRotation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	switch (m_eElementalType)
	{
	case EElementalType::ET_Normal:
	{
		ASpell_MultiShot* pArrow = GetWorld()->SpawnActor<ASpell_MultiShot>(Arrow_Yellow, vPos, vRot,
			tParams);
	}
		break;
	case EElementalType::ET_Fire:
	{
		ASpell_MultiShot* pArrow = GetWorld()->SpawnActor<ASpell_MultiShot>(Arrow_Red, vPos, vRot,
			tParams);
	}
		break;
	case EElementalType::ET_Ice:
	{
		ASpell_MultiShot* pArrow = GetWorld()->SpawnActor<ASpell_MultiShot>(Arrow_Blue, vPos, vRot,
			tParams);
	}
		break;
	}
	State.fTierGage_1 = 0.f;
}

void AGuardian_Archer::ExplosionShot()
{
	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

	FRotator vRot = GetActorRotation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	ASpell_ExplosionArrow* pArrow = GetWorld()->SpawnActor<ASpell_ExplosionArrow>(ExplosionArrow, vPos, vRot,
		tParams);
}

void AGuardian_Archer::IceArrowShow()
{
	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

	FRotator vRot = GetActorRotation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	ASpell_IceArrow* pArrow = GetWorld()->SpawnActor<ASpell_IceArrow>(IceArrow, vPos, vRot,
		tParams);
}

void AGuardian_Archer::StaticArrowShot()
{
	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

	FRotator vRot = GetActorRotation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	ASpell_StaticArrow* pArrow = GetWorld()->SpawnActor<ASpell_StaticArrow>(StaticArrow, vPos, vRot,
		tParams);
}

void AGuardian_Archer::Tier2Skill()
{
	if (m_eElementalType == EElementalType::ET_Normal)
	{
		StaticArrowShot();
	}
	else if (m_eElementalType == EElementalType::ET_Fire)
	{
		ExplosionShot();
	}
	else if (m_eElementalType == EElementalType::ET_Ice)
	{
		IceArrowShow();
	}
}

void AGuardian_Archer::Tier3Skill()
{
	if (m_pDecal)
	{
		if (m_pDecal->GetDecalSkillOn())
		{
			Ultimate();

			m_pDecal->EnableDecal(false);
			m_pDecal->SetDecalSkillOn(false);
		}
	}
}

void AGuardian_Archer::RainOfArrowSkill()
{
	//ºÒÈ­»ì ±× ¶¥ ÀÌÆåÆ® »ý¼º

	FRotator vRot = GetActorRotation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;


	ASpell_RainofArrow* pArrow = GetWorld()->SpawnActor<ASpell_RainofArrow>(RainOfArrow, FVector::ZeroVector, vRot,
		tParams);
}

void AGuardian_Archer::CrystalArrowSkill()
{
	FVector TargetLoc = m_pDecal->GetActorLocation();
	TargetLoc.Z = 0.f;
	FVector MyLoc = GetActorLocation();
	MyLoc.Z = 0.f;

	FVector vDir = TargetLoc - MyLoc;
	vDir.Normalize();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;
	
	FRotator vRot= FRotator(0.f, vDir.Rotation().Yaw, 0.f);

	SetActorRotation(vRot);

	ASpell_CrystalArrow* pArrow = GetWorld()->SpawnActor<ASpell_CrystalArrow>(CrystalArrow,GetActorLocation(), vRot,
		tParams);
}

void AGuardian_Archer::EraseTarget()
{
	Target = nullptr;
	bTarget = false;
}

void AGuardian_Archer::SetAI(EGUARDIAN_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Archer::CreateDecal()
{
	switch (m_eElementalType)
	{
	case EElementalType::ET_Normal:
	{
		m_pDecal= GetWorld()->SpawnActor<AActor_Decal>(YellowDecal,
			FVector::ZeroVector, FRotator(0.f, 0.f, 0.f));
		m_pDecal->EnableDecal(false);
	}
		break;
	case EElementalType::ET_Fire:
	{
		m_pDecal = GetWorld()->SpawnActor<AActor_Decal>(RedDecal,
			FVector::ZeroVector, FRotator(0.f, 0.f, 0.f));
		m_pDecal->EnableDecal(false);
	}
		break;
	case EElementalType::ET_Ice:
	{
		m_pDecal = GetWorld()->SpawnActor<AActor_Decal>(BlueDecal,
			FVector::ZeroVector, FRotator(0.f, 0.f, 0.f));
		m_pDecal->EnableDecal(false);
	}
		break;
	}
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

void AGuardian_Archer::ChangeAnimation(EGuardianAnimType eType)
{
	if (IsValid(Animation))
		Animation->ChangeAnimType(eType);
}
