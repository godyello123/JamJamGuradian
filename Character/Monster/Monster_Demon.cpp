// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Demon.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_Demon.h"
#include "../../NormalActor/DemonGate.h"


AMonster_Demon::AMonster_Demon()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/FlyingDemon/FlyingDemonSK.FlyingDemonSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Demon, AnimAsset, "AnimBlueprint'/Game/02Monster/05Demon/Demon_Anim.Demon_Anim_C'");

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
	SetMonsterState(10, 10, 10, 100, 100);
}

void AMonster_Demon::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
}

bool AMonster_Demon::IsDie()
{
    return bDie;
}

void AMonster_Demon::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_Demon>(GetMesh()->GetAnimInstance());

}

void AMonster_Demon::Tick(float DeltaTime)
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

void AMonster_Demon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_Demon::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

	return State.iHP;
}

void AMonster_Demon::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
		Animation->ChangeAnimType(eType);
}

void AMonster_Demon::Attack()
{
	if (Target)
	{
		AController* Ai = GetController<AController>();
		FDamageEvent DmgEvent;
		Target->TakeDamage(State.Damage, DmgEvent, Ai, this);
	}
}

void AMonster_Demon::Move()
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

	//'5' 나중에 상수 빼고 몬스터들마다 변수로 처리 해야댐
	if (fDist < 5.f)
	{
		NextMovePoint();
	}
}

void AMonster_Demon::Skill()
{
}

bool AMonster_Demon::CheckTargetDistance()
{
	//'6' 상수 빼고 나중에 변수로 처리 해야함.

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
