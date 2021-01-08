// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Knight.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Knight.h"



AGuardian_Knight::AGuardian_Knight()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/FootmanSK.FootmanSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Knight, AnimData, "AnimBlueprint'/Game/01Guardian/01Knight/Knight_Anim.Knight_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	SetState(10, 10, 10, 1.f);

	fAttackDist = 200.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;
	Target = nullptr;
	bAttack = false;
	bTarget = false;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Sword = nullptr;
	Shield = nullptr;
	/*LoadSword(TEXT("index_03_r"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Sword01SM.Sword01SM'"));
	Sword->SetActorRotation(FRotator(0.f, 0.f, -90.f));
	LoadShield(TEXT("hand_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Shield01SM.Shield01SM'"));*/

}

void AGuardian_Knight::AttackEnable(bool bEnable)
{
	bAttack = bEnable;
}

bool AGuardian_Knight::IsAttack() const
{
	return bAttack;
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
	//Sword->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	LoadShield(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Shield01SM.Shield01SM'"));
	Shield->SetActorRotation(FRotator(0.f, -20.f, 0.f));
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

	if (!Target && !bTarget)
	{
		DetectTime += DeltaTime;

		if (DetectTime >= DetectTimeMax)
		{
			SearchTarget();
			DetectTime = 0.f;
		}
	}
	else if (Target!=nullptr&&!bTarget)
	{
		CheckDistance();
	}
	else if (!Target && bTarget)
	{
		bTarget = false;
	}

	if (Target && bTarget)
	{
		bool bCheck = CheckDistance();
		if (bCheck)
		{
			if (State.iMP >= State.iMPMax)
			{
				SwordStrike();
			}
			else
			{
				Attack();
			}
		}

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

void AGuardian_Knight::Attack()
{
	if (!bAttack)
	{
		int32 iValue = FMath::RandRange(1, 100);

		if (iValue <= 10)
		{
			bCritical = true;
		}

		if (IsValid(Animation))
			Animation->ChangeAnimType(EGuardianAnimType::GAT_Attack);
	}
}

void AGuardian_Knight::SwordStrike()
{
}

void AGuardian_Knight::SearchTarget()
{
	Target = nullptr;

	Animation->ChangeAnimType(EGuardianAnimType::GAT_Idle);

	FVector StartLoc = GetActorLocation();

	FVector TargetLoc = FVector(StartLoc.X + fAttackDist, StartLoc.Y + fAttackDist, StartLoc.Z + fAttackDist);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> HitRetArray;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), StartLoc, StartLoc, fAttackDist, TEXT("BlockAll"), false, IgnoreActors,
		EDrawDebugTrace::Type::ForOneFrame, HitRetArray, true);

	if (isHit)
	{
		int32 iSize = HitRetArray.Num();
		for (int32 i = 0; i < iSize; ++i)
		{
			if (HitRetArray[i].Component.Get()->GetCollisionProfileName() == TEXT("Monster"))
			{
				AActor* pTarget = HitRetArray[0].Actor.Get();

				AMonster* Mon= (AMonster*)pTarget;

				if (!Mon->IsDead())
				{
					Target = pTarget;
					bTarget = true;
				}
				
				return;
			}
		}
	}

}

bool AGuardian_Knight::CheckDistance()
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
		Animation->ChangeAnimType(EGuardianAnimType::GAT_Idle);

		return false;
	}
	else
	{
		bTarget = true;

		FVector vDir = TargetLoc - MyLoc;
		vDir.Normalize();

		SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

		return true;
	}

	return false;
}

void AGuardian_Knight::AttackToTarget()
{
	if (bTarget)
	{
		AController* AI = GetController<AController>();

		FDamageEvent DmgEvent;

		float fHp=Target->TakeDamage(State.Damage, DmgEvent, AI,this);

		if (fHp <= 0.f)
		{
			Target = nullptr;
			bTarget = false;
		}

		PrintViewport(1.f, FColor::Red, TEXT("TakeDamage"));
	}
}
