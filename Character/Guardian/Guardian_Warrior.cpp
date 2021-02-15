// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Warrior.h"
#include "Summoner.h"
#include "Guardian_Knight.h"
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

	GetClassAsset(AEffect, EffectAsset, "Blueprint'/Game/06Effect/BP_Effect_Knight.BP_Effect_Knight_C'");

	if (EffectAsset.Succeeded())
		Effect = EffectAsset.Class;

	SetState(5, 10, 2, 1.f);

	//fAttackDist = 200.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	bAttack = false;


	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Sword = nullptr;
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

void AGuardian_Warrior::NormalLevelUp()
{
	Dead();
	//이펙트 넣어주기

	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(LightningLevelUp_EffectAsset, vLoc, vRot);
	AGuardian_Knight* pHunter = GetWorld()->SpawnActor<AGuardian_Knight>(vLoc, vRot);
}

void AGuardian_Warrior::FireLevelUp()
{
	Dead();
	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(FireLevelUp_EffectAsset, vLoc, vRot);
	AGuardian_Knight* pHunter = GetWorld()->SpawnActor<AGuardian_Knight>(vLoc, vRot);
}

void AGuardian_Warrior::IceLevelUp()
{
	Dead();
	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();
	AEffect_LevelUp* pEffect = GetWorld()->SpawnActor<AEffect_LevelUp>(IceLevelUp_EffectAsset, vLoc, vRot);
	AGuardian_Knight* pHunter = GetWorld()->SpawnActor<AGuardian_Knight>(vLoc, vRot);
}

void AGuardian_Warrior::Dead()
{
	Super::Dead();
	Sword->Destroy();
}

void AGuardian_Warrior::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Warrior>(GetMesh()->GetAnimInstance());

	LoadSword(TEXT("weaponShield_r"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Sword01SM.Sword01SM'"));

	SetFillMP(0.5);
}

void AGuardian_Warrior::SetAI(EGUARDIAN_AI _eAI)
{
	eAI = _eAI;
}

void AGuardian_Warrior::LoadSword(const FString& strSocket, const FString& strMeshPath)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	Sword = GetWorld()->SpawnActor<AActor_Weapon>(FVector::ZeroVector,
		FRotator::ZeroRotator, params);

	Sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
		*strSocket);

	Sword->LoadMesh(strMeshPath);
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

void AGuardian_Warrior::Attack()
{
	if (State.iMP >= State.iMPMax)
		ChangeAnimation(EGuardianAnimType::GAT_Skill);
	//else
	//	ChangeAnimation(EGuardianAnimType::GAT_Attack);

}

void AGuardian_Warrior::Skill()
{
	CrushAttack();
}

void AGuardian_Warrior::SearchTarget()
{
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
					eAI = EGUARDIAN_AI::Attack;
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
		eAI = EGUARDIAN_AI::Idle;
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
			eAI = EGUARDIAN_AI::Idle;
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

void AGuardian_Warrior::CreateEffect()
{
	FVector vPos = Target->GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEffect* pEffect = GetWorld()->SpawnActor<AEffect>(Effect, vPos, GetActorRotation(),
		tParams);
}
