// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_RatAssassin.h"
#include "AIController.h"
#include "../../Animation/Monster/Anim_RatAssassin.h"
#include "../../NormalActor/DemonGate.h"

AMonster_RatAssassin::AMonster_RatAssassin()
{
	TICKON;

	GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/RPGMonsterWave2PBR/Mesh/RatAssassin/RatAssassinSK.RatAssassinSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_RatAssassin, AnimAsset, "AnimBlueprint'/Game/02Monster/08RatAssassin/Rat_Anim.Rat_Anim_C'");

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

void AMonster_RatAssassin::Die()
{
	bDie = true;
	Animation->ChangeAnimType(EMonsterAnimType::MAT_Die);
}

bool AMonster_RatAssassin::IsDie()
{
	return bDie;
}

void AMonster_RatAssassin::BeginPlay()
{
	Super::BeginPlay();

	Animation = Cast<UAnim_RatAssassin>(GetMesh()->GetAnimInstance());
}

void AMonster_RatAssassin::Tick(float DeltaTime)
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

void AMonster_RatAssassin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMonster_RatAssassin::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster_RatAssassin::ChangeAnim(EMonsterAnimType eType)
{
	if (Animation)
	{
		Animation->ChangeAnimType(eType);
	}
}

void AMonster_RatAssassin::Attack()
{
	if (Target)
	{
		AController* Ai = GetController<AController>();
		FDamageEvent DmgEvent;
		Target->TakeDamage(State.Damage, DmgEvent, Ai, this);
	}
}

void AMonster_RatAssassin::Move()
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

	//상수 값 대신 각 몬스터별 사거리에 맞는 값으로 대체해야함
	//그런 디테일은 나중에 잡는다.
	if (fDist < 5.f)
	{
		NextMovePoint();
	}
}

void AMonster_RatAssassin::Skill()
{
}

bool AMonster_RatAssassin::CheckTargetDistance()
{	
	//'6'상수값 대신 몬스터별로 
	 //사거리에 맞는 값으로 변수로 대체 해야함
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
