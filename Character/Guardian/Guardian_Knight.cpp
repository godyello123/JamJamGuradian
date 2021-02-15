// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Knight.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Knight.h"



AGuardian_Knight::AGuardian_Knight()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/TemplarSK.TemplarSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Knight, AnimData, "AnimBlueprint'/Game/01Guardian/01Knight/Knight_Anim.Knight_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	GetClassAsset(AEffect, EffectAsset, "Blueprint'/Game/06Effect/BP_Effect_Knight.BP_Effect_Knight_C'");

	if (EffectAsset.Succeeded())
		Effect = EffectAsset.Class;

	SetState(5, 10, 2, 1.f);

	//fAttackDist = 10000.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	bAttack = false;

	SetFillMP(0.44);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));
	Sword = nullptr;
	Shield = nullptr;
	
	eAI = EGUARDIAN_AI::Idle;

	//Tags.Add("kngiht");

}

void AGuardian_Knight::SetAI(EGUARDIAN_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Knight::ChangeAnimation(EGuardianAnimType eType)
{
	if (IsValid(Animation))
		Animation->ChangeAnimType(eType);
}

void AGuardian_Knight::LevelUP(ELevelUpType eType)
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

void AGuardian_Knight::NormalLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(LightningLevelUp_EffectAsset, vLoc, vRot);
}

void AGuardian_Knight::FireLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(FireLevelUp_EffectAsset, vLoc, vRot);
}

void AGuardian_Knight::IceLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(IceLevelUp_EffectAsset, vLoc, vRot);
}

void AGuardian_Knight::Dead()
{
	Super::Dead();
	Sword->Destroy();
	Shield->Destroy();
}

void AGuardian_Knight::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Knight>(GetMesh()->GetAnimInstance());

	LoadSword(TEXT("weaponShield_r"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Sword01SM.Sword01SM'"));
	LoadShield(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Shield01SM.Shield01SM'"));
	Shield->SetActorRotation(FRotator(0.f, -20.f, 0.f));
	Sword->SetActorRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));
	Shield->SetActorRelativeScale3D(FVector(1.2f, 1.2f, 1.2f));
	FString Name = GetDebugName(this);

	
	SetFillMP(0.5);

	for (int32 i = 0; i < Tags.Num(); ++i)
	{
		PrintViewport(10.f, FColor::Black, Tags[i].ToString());
	}
}

void AGuardian_Knight::LoadSword(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride=
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	Sword = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	Sword->LoadMesh(strMeshPath);
}

void AGuardian_Knight::LoadShield(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	Shield = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	Shield->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	Shield->LoadMesh(strMeshPath);
}

void AGuardian_Knight::Tick(float DeltaTime)
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

void AGuardian_Knight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AGuardian_Knight::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void AGuardian_Knight::Motion()
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

void AGuardian_Knight::Attack()
{
	if (State.iMP >= State.iMPMax)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
	//else
	//	ChangeAnimation(EGuardianAnimType::GAT_Attack);

	//ChangeAnimation(EGuardianAnimType::GAT_Attack);
}

void AGuardian_Knight::Skill()
{
	PowerStrike();
}

void AGuardian_Knight::SearchTarget()
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

void AGuardian_Knight::CreateEffect()
{
	
	FVector vPos = Target->GetActorLocation();
	
	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEffect* pEffect = GetWorld()->SpawnActor<AEffect>(Effect, vPos, GetActorRotation(),
		tParams);
}

void AGuardian_Knight::Groggy()
{
	ChangeAnimation(EGuardianAnimType::GAT_Groggy);
}

void AGuardian_Knight::Victory()
{
	ChangeAnimation(EGuardianAnimType::GAT_Victory);
}

bool AGuardian_Knight::CheckDistance()
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
		eAI = EGUARDIAN_AI::Idle;
		return false;
	}

	return false;
}

void AGuardian_Knight::AttackToTarget()
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

void AGuardian_Knight::PowerStrike()
{
	//강하게 한대 때리기
	if (bTarget && Target)
	{
		//이펙트 생성
		CreateEffect();

		AController* AI = GetController<AController>();

		AMonster* pMonster = Cast<AMonster>(Target);
		pMonster->SetGroggyTime(0.5f);

		FDamageEvent DmgEvent;

		float fDmg = State.Damage * 1.5;

		float fHp = Target->TakeDamage(fDmg, DmgEvent, AI, this);
		
		if (fHp <= 0.f)
		{
			Target = nullptr;
			bTarget = false;
		}

		State.iMP = 0;

	}

}

void AGuardian_Knight::ShowUI(bool bShow)
{
	if (bShow)
	{
		PrintViewport(2.f, FColor::Magenta, TEXT("SHOW UI : Knight"));
	}
	else
	{
		PrintViewport(2.f, FColor::Magenta, TEXT("HIDE UI : Knight"));
	}
}
