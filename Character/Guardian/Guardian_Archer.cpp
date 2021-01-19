// Fill out your copyright notice in the Description page of Project Settings.


#include "Guardian_Archer.h"
#include "Summoner.h"
#include "../Monster/Monster.h"
#include "../../NormalActor/Actor_Weapon.h"
#include "../../Animation/Guardian/Anim_Archer.h"



AGuardian_Archer::AGuardian_Archer()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, AssetData, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/ApprenticeSK.ApprenticeSK'");

	if (AssetData.Succeeded())
		GetMesh()->SetSkeletalMesh(AssetData.Object);

	GetClassAsset(UAnim_Archer, AnimData, "AnimBlueprint'/Game/01Guardian/02Archer/Archer_Anim.Archer_Anim_C'");

	if (AnimData.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimData.Class);

	GetClassAsset(ASpell_MultiShot, ArrowAsset, "Blueprint'/Game/05Spell/Multishot_BP.Multishot_BP_C'");

	if (ArrowAsset.Succeeded())
		Arrow = ArrowAsset.Class;

	SetState(5, 10, 10, 1.f);

	//fAttackDist = 400.f;
	bCritical = false;
	CriticalChance = 10;
	CriticalRatio = 1.5;



	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	Bow = nullptr;

	eAI = EARCHER_AI::Idle;
}

void AGuardian_Archer::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Archer>(GetMesh()->GetAnimInstance());

	LoadBow(TEXT("weaponShield_l"), TEXT("StaticMesh'/Game/ModularRPGHeroesPBR/Meshes/Weapons/Bow01SM.Bow01SM'"));
	
	SetFillMP(0.5);
}

void AGuardian_Archer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Motion();
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

void AGuardian_Archer::LevelUP(ELevelUpType eType)
{
}

void AGuardian_Archer::Motion()
{
	switch (eAI)
	{
	case EARCHER_AI::Idle:
		SearchTarget();
		break;
	case EARCHER_AI::Attack:
		CheckDistance();
		break;
	case EARCHER_AI::Victory:
		Victory();
		break;
	case EARCHER_AI::Groggy:
		Groggy();
		break;
	}
}

void AGuardian_Archer::Attack()
{
	//if (State.iMP >= State.iMPMax)
	//	ChangeAnimation(EGuardianAnimType::GAT_Skill);
	//else
	//	ChangeAnimation(EGuardianAnimType::GAT_Attack);

	ChangeAnimation(EGuardianAnimType::GAT_Attack);
}

void AGuardian_Archer::Skill()
{
}

void AGuardian_Archer::SearchTarget()
{
	if (Target || bTarget)
	{
		eAI = EARCHER_AI::Attack;
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

					eAI = EARCHER_AI::Attack;
				}

				return;
			}
		}
	}
}

bool AGuardian_Archer::CheckDistance()
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
		eAI = EARCHER_AI::Idle;
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
			eAI = EARCHER_AI::Idle;
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

void AGuardian_Archer::MultiShot()
{
	for (int32 i = -1; i < 2; ++i)
	{
		FVector vPos = GetActorLocation() + GetActorForwardVector() * 200.f;

		FRotator vRot = GetActorRotation();

		vRot.Yaw += i * 30.f;

		FActorSpawnParameters tParams;

		tParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		tParams.Owner = this;

		ASpell_MultiShot* pArrow = GetWorld()->SpawnActor<ASpell_MultiShot>(Arrow, vPos, vRot,
			tParams);
	}
	

	State.iMP = 0;
}

void AGuardian_Archer::ShowUI(bool bShow)
{
	if (bShow)
	{
		PrintViewport(2.f, FColor::Magenta, TEXT("SHOW UI : Archer"));
	}
	else
	{
		PrintViewport(2.f, FColor::Magenta, TEXT("HIDE UI : Archer"));
	}
}

void AGuardian_Archer::SetAI(EARCHER_AI _eAI)
{
	eAI = _eAI;
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
