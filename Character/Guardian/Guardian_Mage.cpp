// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Mage.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Mage.h"
#include "../../Controller/SummonerController.h"
#include "../../GameMode/DefenstPlayerState.h"


AGuardian_Mage::AGuardian_Mage()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/MageSK.MageSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Mage, AnimData, "AnimBlueprint'/Game/01Guardian/04Mage/Mage_Anim.Mage_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	GetClassAsset(ASpell_MagicMissile, SpellAsset1, "Blueprint'/Game/05Spell/MagicMissile_BP_Blue.MagicMissile_BP_Blue_C'");

	if (SpellAsset1.Succeeded())
		Bolt_Blue = SpellAsset1.Class;

	GetClassAsset(ASpell_MagicMissile, SpellAsset2, "Blueprint'/Game/05Spell/MagicMissile_BP_red.MagicMissile_BP_red_C'");

	if (SpellAsset2.Succeeded())
		Bolt_Red = SpellAsset2.Class;

	GetClassAsset(ASpell_MagicMissile, SpellAsset3, "Blueprint'/Game/05Spell/MagicMissile_BP_yellow.MagicMissile_BP_yellow_C'");

	if (SpellAsset3.Succeeded())
		Bolt_Yellow = SpellAsset3.Class;

	GetClassAsset(ASpell_FireField, SpellAsset4, "Blueprint'/Game/05Spell/Spell_FireField_BP.Spell_FireField_BP_C'");

	if (SpellAsset4.Succeeded())
		FireField = SpellAsset4.Class;

	GetClassAsset(ASpell_Crystalize, SpellAsset5, "Blueprint'/Game/05Spell/Crystalize_BP.Crystalize_BP_C'");

	if (SpellAsset5.Succeeded())
		Crystalize = SpellAsset5.Class;

	GetClassAsset(ASpell_Thunder, SpellAsset6, "Blueprint'/Game/05Spell/BP_Thunder.BP_Thunder_C'");

	if (SpellAsset6.Succeeded())
		Thunder = SpellAsset6.Class;

	//SetState(5, 10, 1, 1.f);

	//fAttackDist = 300.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	bAttack = false;

	//SetFillMP(0.64);


	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	Wand = nullptr;

	eAI = EGUARDIAN_AI::Idle;
}

void AGuardian_Mage::Dead()
{
	Super::Dead();
	Wand->Destroy();
}

void AGuardian_Mage::BeginPlay()
{
	Super::BeginPlay();

	LoadWand(TEXT("weaponShield_r"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Wand01SM.Wand01SM'"));

	Animation = Cast<UAnim_Mage>(GetMesh()->GetAnimInstance());

	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();

	m_iDmgLevel = pState->GetNormalDmg();

	//State.AttackSpeed = m_iDmgLevel + (m_iDmgLevel * 1);
	State.iDamage = State.iDamage + (m_iDmgLevel * 5);

	Wand->SetActorRelativeScale3D(FVector(1.f, 1.f, 1.f));

	SetState(20, 3.f, 8.f, 15.f, 1.f);
	SetFillTierGage_1(0.7f);
	SetFillTierGage_2(0.f);
	SetFillTierGage_3(0.f);
}

void AGuardian_Mage::SetAI(EGUARDIAN_AI _eAI)
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

	FillUpTierGage_1(m_fFillTierGage_1, DeltaTime);
	FillUpTierGage_2(m_fFillTierGage_2, DeltaTime);


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
	if(State.fTierGage_1>=State.fTierGageMax_1||
		State.fTierGage_2>=State.fTierGageMax_2||
		State.fTierGage_3>=State.fTierGageMax_3)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
}

void AGuardian_Mage::Groggy()
{
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Mage::Skill()
{
	if (State.fTierGage_3 >= State.fTierGageMax_3)
	{
		
	}

	if (State.fTierGage_2 >= State.fTierGageMax_2)
	{
		MageTier2Skill();
		State.fTierGage_2 = 0.f;
	}

	if (State.fTierGage_1 >= State.fTierGageMax_1)
	{
		MagicMissaile();
	}
}

void AGuardian_Mage::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

void AGuardian_Mage::LevelUp(EGUARDIANLEVEL eLevel, EElementalType eType)
{
	switch (eLevel)
	{
	case EGUARDIANLEVEL::GL_LEVEL1:
	{
		Mage_Tier2(eType);

	}
	break;
	case EGUARDIANLEVEL::GL_LEVEL2:
	{
		Mage_Tier3(eType);
	}
	break;
	case EGUARDIANLEVEL::GL_LEVEL3:
	{

	}
	break;
	}
}

void AGuardian_Mage::SearchTarget()
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

void AGuardian_Mage::Targeting(const FVector& vLoc)
{
	PrintViewport(1.f, FColor::Yellow, TEXT("MAGE 3"));
}

void AGuardian_Mage::Ultimate()
{
	ChangeAnimation(EGuardianAnimType::GAT_Ultimate);
}

void AGuardian_Mage::Mage_Tier2(EElementalType eType)
{
	USkeletalMesh* pMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/PrinceSK.PrinceSK'"));
	GetMesh()->SetSkeletalMesh(pMesh);
	GetMesh()->SetWorldScale3D(FVector(1.1f, 1.1f, 1.1f));
	SetGuardianLevel(EGUARDIANLEVEL::GL_LEVEL2);
	SetElementalType(eType);
	SetFillTierGage_2(0.7f);
}

void AGuardian_Mage::Mage_Tier3(EElementalType eType)
{
	USkeletalMesh* pMesh = LoadObject<USkeletalMesh>(nullptr, TEXT("SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/BattleMageSK.BattleMageSK'"));
	GetMesh()->SetSkeletalMesh(pMesh);
	GetMesh()->SetWorldScale3D(FVector(1.2f, 1.2f, 1.2f));
	SetGuardianLevel(EGUARDIANLEVEL::GL_LEVEL3);
	SetElementalType(eType);
	SetFillTierGage_2(0.7f);
	HideUI();
}

void AGuardian_Mage::MageTier2Skill()
{
	if (m_eElementalType == EElementalType::ET_Normal)
	{
		ThunderSkill();
	}
	else if (m_eElementalType == EElementalType::ET_Fire)
	{
		FireFieldSkill();
	}
	else if (m_eElementalType == EElementalType::ET_Ice)
	{
		CrytalizeSkill();
	}
}

void AGuardian_Mage::FireFieldSkill()
{
	FVector vPos = Target->GetActorLocation();
	FVector vFwd = Target->GetActorForwardVector();

	vPos += vFwd * 30.f;

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	ASpell_FireField* pMagic = GetWorld()->SpawnActor<ASpell_FireField>(FireField, vPos, GetActorRotation(),
		tParams);
}

void AGuardian_Mage::CrytalizeSkill()
{
	FVector vPos = Target->GetActorLocation();
	FVector vFwd = Target->GetActorForwardVector();

	vPos += vFwd * 30.f;

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	ASpell_Crystalize* pMagic = GetWorld()->SpawnActor<ASpell_Crystalize>(Crystalize, vPos, Target->GetActorRotation(),
		tParams);
}

void AGuardian_Mage::ThunderSkill()
{
	FVector vPos = Target->GetActorLocation();
	FVector vFwd = Target->GetActorForwardVector();

	vPos += vFwd * 30.f;

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	ASpell_Thunder* pMagic = GetWorld()->SpawnActor<ASpell_Thunder>(Thunder, vPos, Target->GetActorRotation(),
		tParams);
}

bool AGuardian_Mage::CheckDistance()
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

void AGuardian_Mage::AttackToTarget()
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

void AGuardian_Mage::MagicMissaile()
{
	//스킬 만들기
	FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	switch (m_eElementalType)
	{
	case EElementalType::ET_Normal:
	{
		ASpell_MagicMissile* pMagic = GetWorld()->SpawnActor<ASpell_MagicMissile>(Bolt_Yellow, vPos, GetActorRotation(),
			tParams);
	}
		break;
	case EElementalType::ET_Fire:
	{
		ASpell_MagicMissile* pMagic = GetWorld()->SpawnActor<ASpell_MagicMissile>(Bolt_Red, vPos, GetActorRotation(),
			tParams);

	}
		break;
	case EElementalType::ET_Ice:
	{
		ASpell_MagicMissile* pMagic = GetWorld()->SpawnActor<ASpell_MagicMissile>(Bolt_Blue, vPos, GetActorRotation(),
			tParams);
	}
		break;
	}

	State.fTierGage_1 = 0.f;
}

void AGuardian_Mage::EraseTarget()
{
	Target = nullptr;
	bTarget = false;
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

