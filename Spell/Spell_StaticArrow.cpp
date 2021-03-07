// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_StaticArrow.h"
#include "../Character/Monster/Monster.h"
#include "../Character/Guardian/Guardian_Archer.h"

ASpell_StaticArrow::ASpell_StaticArrow()
{
	fLifeTime = 0.f;
	fLifeTimeMax = 10;

	m_iTargetCount = 0;

	GetClassAsset(AEffect_Static, EffectAsset, "Blueprint'/Game/06Effect/BP_StaticEffect.BP_StaticEffect_C'");

	if (EffectAsset.Succeeded())
		Effect_Static = EffectAsset.Class;

	Mesh->SetEnableGravity(false);

	Target = nullptr;
}

void ASpell_StaticArrow::SetTargetCount(int32 iCount)
{
	m_iTargetCount = iCount;
}

int32 ASpell_StaticArrow::GetTargetCount() const
{
	return m_iTargetCount;
}

void ASpell_StaticArrow::SetTargetCountMax(int32 iCount)
{
	m_iTargetCountMax = iCount;
}

int32 ASpell_StaticArrow::GetTargetCountMax() const
{
	return m_iTargetCountMax;
}

void ASpell_StaticArrow::BeginPlay()
{
	Super::BeginPlay();

	m_iTargetCount = 0;
	m_iTargetCountMax = 2;

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_StaticArrow::CollisionBeginOverlap);

	Mesh->SetEnableGravity(false);

	SetSpellDmgRate(0.6);
}

void ASpell_StaticArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	FVector vPos = GetActorLocation();

	FVector vForward = GetActorForwardVector();

	vPos = vPos + (vForward * 1000 * DeltaTime);

	SetActorLocation(vPos);

	fLifeTime += DeltaTime;

	if (fLifeTime >= fLifeTimeMax)
	{
		//CreateEffect();
		this->Destroy();
	}
}

bool ASpell_StaticArrow::Check()
{
	FVector StartLoc = GetActorLocation();

	FVector TargetLoc = FVector(StartLoc.X + 200, StartLoc.Y + 200, StartLoc.Z + 200);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> HitRetArray;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), StartLoc, StartLoc, 500, TEXT("BlockAll"), false, IgnoreActors,
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
					AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

					AMonster* pMon2 = Cast<AMonster>(pArcher->GetTarget());

					if (Mon->GetName() != pMon2->GetName())
					{
						if (Target)
						{
							if (Mon->GetName() != Target->GetName())
								Target = pTarget;
						}
						else
							Target = pTarget;

						return true;
					}
				}
			}
		}
		return false;
	}

	return false;
}

void ASpell_StaticArrow::CreateEffect()
{
	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEffect_Static* pEffect = GetWorld()->SpawnActor<AEffect_Static>(Effect_Static, GetActorLocation(), GetActorRotation(),
		tParams);

	if (m_iTargetCount <= m_iTargetCountMax)
	{
		if (Check())
			CreateStatic();
		else
			Destroy();
	}
}

void ASpell_StaticArrow::CreateStatic()
{
	AMonster* pMon = Cast<AMonster>(Target);

	if (pMon->GetMonsterState().iHP <= 0)
	{
		return;
	}

	FVector TargetLoc = Target->GetActorLocation();
	TargetLoc.Z = 0.f;
	FVector MyLoc = GetActorLocation();
	MyLoc.Z = 0.f;

	FVector vDir = TargetLoc - MyLoc;
	vDir.Normalize();

	FRotator vRot = FRotator(0.f, vDir.Rotation().Yaw, 0.f);

	SetActorRotation(FRotator(0.f, vDir.Rotation().Yaw, 0.f));

	++m_iTargetCount;
}

void ASpell_StaticArrow::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FDamageEvent DmgEvent;

	AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

	float fDmg = pArcher->GetState().iDamage*GetSpellDmgRate();

	if (IsValid(pArcher))
	{
		float fHp = OtherActor->TakeDamage(fDmg, DmgEvent, pArcher->GetController(), this);

		if (fHp <= 0.f)
		{
			pArcher->EraseTarget();
		}

		CreateEffect();
	}
}
