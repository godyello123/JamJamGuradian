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

	GetClassAsset(AProjectile, ProjectileData, "Blueprint'/Game/07Projectile/Projectile_Knight.Projectile_Knight_C'");

	if (ProjectileData.Succeeded())
		Projectile = ProjectileData.Class;

	SetState(5, 10, 10, 1.f);

	//fAttackDist = 10000.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;

	bAttack = false;


	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Sword = nullptr;
	Shield = nullptr;
	
	eAI = EKNIGHT_AI::Idle;

	//Tags.Add("kngiht");

}

void AGuardian_Knight::SetAI(EKNIGHT_AI _eAI)
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

void AGuardian_Knight::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Knight>(GetMesh()->GetAnimInstance());

	LoadSword(TEXT("weaponShield_r"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Sword01SM.Sword01SM'"));
	LoadShield(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Shield01SM.Shield01SM'"));
	Shield->SetActorRotation(FRotator(0.f, -20.f, 0.f));

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

	Motion();
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
	case EKNIGHT_AI::Idle:
		SearchTarget();
		break;
	case EKNIGHT_AI::Attack:
		CheckDistance();
		break;
	case EKNIGHT_AI::Victory:
		Victory();
		break;
	case EKNIGHT_AI::Groggy:
		Groggy();
		break;
	}
}

void AGuardian_Knight::Attack()
{
	//if (State.iMP >= State.iMPMax)
	//	ChangeAnimation(EGuardianAnimType::GAT_Skill);
	//else
	//	ChangeAnimation(EGuardianAnimType::GAT_Attack);

	ChangeAnimation(EGuardianAnimType::GAT_Attack);
}

void AGuardian_Knight::Skill()
{

}

void AGuardian_Knight::SearchTarget()
{
	if (Target || bTarget)
	{
		eAI = EKNIGHT_AI::Attack;
		return;
	}

	FVector StartLoc = GetActorLocation();

	FVector TargetLoc = FVector(StartLoc.X + fAttackDist, StartLoc.Y + fAttackDist, StartLoc.Z + fAttackDist);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> HitRetArray;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), StartLoc, StartLoc, fAttackDist, TEXT("BlockAll"), false, IgnoreActors,
		EDrawDebugTrace::Type::ForDuration, HitRetArray, true);

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

					eAI = EKNIGHT_AI::Attack;
				}

				return;
			}
		}
	}
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
		eAI = EKNIGHT_AI::Idle;
		return false;
	}

	return false;
}

void AGuardian_Knight::AttackToTarget()
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
			eAI = EKNIGHT_AI::Idle;
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

void AGuardian_Knight::PowerStrike()
{
	//강하게 한대 때리기
	if (bTarget && Target)
	{
		AController* AI = GetController<AController>();

		FDamageEvent DmgEvent;

		float fDmg = State.Damage * 1.5;

		float fHp = Target->TakeDamage(fDmg, DmgEvent, AI, this);

		FVector TargetLoc = Target->GetActorLocation();
		TargetLoc.Z = 0.f;
		FVector MyLoc = GetActorLocation();

		float fDist = FVector::Distance(TargetLoc, MyLoc);

		if (fDist > fAttackDist)
		{
			Target = nullptr;
			bTarget = false;
			//bAttack = false;
			eAI = EKNIGHT_AI::Idle;
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
