// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Beholder.h"
#include "Anim_Beholder.h"
#include "AIController.h"
#include "DemonGate.h"


AMonster_Beholder::AMonster_Beholder()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/Beholder/BeholderSK.BeholderSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Beholder, AnimAsset,"AnimBlueprint'/Game/02Monster/01Beholder/Beholder_Anim.Beholder_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetCollisionProfileName(TEXT("Monster"));

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	bDie = false;

	fMPRecovery = 0;
	fDistance = 1000.f;
	SetMonsterState(5, 5, 5, 100, 100);

}

void AMonster_Beholder::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
	//PrintViewport(10.f, FColor::Red, TEXT("Die_Beholder"));
}

void AMonster_Beholder::Attack()
{
	//PrintViewport(10.f, FColor::Red, TEXT("Attack_Beholder"));

	if (Target)
	{
		AController* Ai =GetController<AController>();
		FDamageEvent DmgEvent;
		Target->TakeDamage(State.Damage, DmgEvent, Ai, this);
	}
}

bool AMonster_Beholder::IsDie()
{
	return bDie;
}

void AMonster_Beholder::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Beholder>(GetMesh()->GetAnimInstance());
}

void AMonster_Beholder::Tick(float DeltaTime)
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

void AMonster_Beholder::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_Beholder::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_Beholder::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_Beholder::Move()
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

void AMonster_Beholder::Skill()
{
}

bool AMonster_Beholder::CheckTargetDistance()
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

