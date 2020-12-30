// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Knight.h"
#include "Summoner.h"
#include "Anim_Knight.h"


AGuardian_Knight::AGuardian_Knight()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/FootmanSK.FootmanSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Knight, AnimData, "AnimBlueprint'/Game/01Guardian/Knight_Anim.Knight_Anim_C'");

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

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
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
}

void AGuardian_Knight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//몬스터가 영역 안에 들어왔는지 탐지
	if (!bTarget)
	{
		Animation->ChangeAnimType(EGuardianAnimType::GAT_Idle);
		DetectTime += DeltaTime;

		if (DetectTime >= DetectTimeMax)
		{
			DetectTime -= DetectTimeMax;
			SearchTarget();
		}
	}
	else
	{
		Attack();
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

void AGuardian_Knight::SearchTarget()
{
	FVector StartLoc = GetActorLocation();

	FVector TargetLoc = FVector(StartLoc.X + fAttackDist, StartLoc.Y + fAttackDist, StartLoc.Z + fAttackDist);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> HitRetArray;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), StartLoc, StartLoc, 200.f, TEXT("BlockAll"), false, IgnoreActors,
		EDrawDebugTrace::Type::ForOneFrame, HitRetArray, true);

	if (isHit)
	{
		int32 iSize = HitRetArray.Num();
		for (int32 i = 0; i < iSize; ++i)
		{
			if (HitRetArray[i].Component.Get()->GetCollisionProfileName() == TEXT("Monster"))
			{
				Target = HitRetArray[0].Actor.Get();
				bTarget = true;
				return;
			}
		}
	}

}

void AGuardian_Knight::CheckDistance()
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
	}
}

void AGuardian_Knight::AttackToTarget()
{
	if (bTarget)
	{
		AController* AI = GetController<AController>();

		FDamageEvent DmgEvent;

		Target->TakeDamage(State.Damage, DmgEvent, AI,this);
		PrintViewport(1.f, FColor::Red, TEXT("TakeDamage"));
	}
}
