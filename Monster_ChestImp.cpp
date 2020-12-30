// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_ChestImp.h"
#include "Anim_ChestImp.h"
#include "AIController.h"
#include "DemonGate.h"


AMonster_ChestImp::AMonster_ChestImp()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/ChestMonster/ChestMonsterSK.ChestMonsterSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_ChestImp, AnimAsset, "AnimBlueprint'/Game/02Monster/02ChestImp/ChestImp_Anim.ChestImp_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bDie = false;

	fMPRecovery = 0;
	fDistance = 1000.f;
	SetMonsterState(5, 5, 5, 100, 100);

}

void AMonster_ChestImp::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
	//PrintViewport(10.f, FColor::Red, TEXT("Die_Beholder"));
}

void AMonster_ChestImp::Attack()
{
	//PrintViewport(10.f, FColor::Red, TEXT("Attack_Beholder"));

	if (Target)
	{
		AController* Ai = GetController<AController>();
		FDamageEvent DmgEvent;
		Target->TakeDamage(State.Damage, DmgEvent, Ai, this);
	}
}

bool AMonster_ChestImp::IsDie()
{
	return bDie;
}

void AMonster_ChestImp::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_ChestImp>(GetMesh()->GetAnimInstance());
}

void AMonster_ChestImp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDie)
	{
		if (State.iMP < State.iMPMax)
		{
			fMPRecovery += DeltaTime;

			if (fMPRecovery > 1.f)
			{
				fMPRecovery = 0;
				State.iMP++;
			}
		}


		bool bCheck = CheckTargetDistance();

		if (bCheck)
		{
			//if (State.iMP >= State.iMPMax)
			//{
			//	//스테이지가 높으면 -> 스테이지가 어떤 난이도인지에 따라서 스킬 발동 유무
			//	//Skill();
			//}
			//else
			//{
			//	Attack();
			//}
			ChangeAnim(EMonsterAnimType::MAT_Attack);
		}
		else
		{
			Move();
		}
	}
}

void AMonster_ChestImp::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_ChestImp::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	State.iHP -= DamageAmount;
	if (State.iHP <= 0)
	{
		//죽이기
		if (Animation)
		{
			Die();
		}
	}

	return 0.0f;
}

void AMonster_ChestImp::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_ChestImp::Move()
{
	if (iMovePoint >= RoadArray.Num())
		return;

	AAIController* pAI = GetController<AAIController>();
	FVector vMoveLoc = RoadArray[iMovePoint]->GetActorLocation();
	FVector vMyLoc = GetActorLocation();

	vMoveLoc.Z = vMyLoc.Z;
	pAI->MoveToActor(RoadArray[iMovePoint], -1.f, false, true);

	ChangeAnim(EMonsterAnimType::MAT_Move);

	vMoveLoc.Z = 0.f;
	vMyLoc.Z = 0.f;

	float fDist = FVector::Distance(vMoveLoc, vMyLoc);

	if (fDist < 5.f)
	{
		NextMovePoint();
	}
}

void AMonster_ChestImp::Skill()
{
}

bool AMonster_ChestImp::CheckTargetDistance()
{
	if (iMovePoint > 6)
	{
		if (Target)
		{
			FVector vTargetLoc = Target->GetActorLocation();
			FVector vMyLoc = GetActorLocation();

			vTargetLoc.Z = 0.f;
			vMyLoc.Z = 0.f;

			float fDist = FVector::Distance(vTargetLoc, vMyLoc);

			if (fDist <= fDistance)
				return true;
			else
				return false;

		}

		return false;
	}

	return false;
}


