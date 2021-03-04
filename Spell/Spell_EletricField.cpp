// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_EletricField.h"
#include "../Character/Guardian/Guardian_Mage.h"
#include "../Character/Monster/Monster.h"

ASpell_EletricField::ASpell_EletricField()
{
	particle2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle2"));
	particle2->SetupAttachment(Mesh);

	m_fLifeTime = 0.f;
	m_fMaxLIfeTime = 7.f;

	m_fDamageTime = 0.f;
	m_fDamageMaxTime = 0.3;
}

void ASpell_EletricField::BeginPlay()
{
	Super::BeginPlay();

	Collision->SetEnableGravity(false);
	Mesh->SetEnableGravity(false);

	//Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_EletricField::CollisionBeginOverlap);

	SetSpellDmgRate(0.6);
}

void ASpell_EletricField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;
	m_fDamageTime += DeltaTime;

	if (m_fLifeTime >= m_fMaxLIfeTime)
	{
		Destroy();
	}

	if (m_fDamageTime >= m_fDamageMaxTime)
	{
		Damage();
	}
}

void ASpell_EletricField::Damage()
{
	FVector StartLoc = GetActorLocation();

	FVector TargetLoc = FVector(StartLoc.X + 300, StartLoc.Y + 300, StartLoc.Z + 300);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> HitRetArray;

	bool isHit = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), StartLoc, StartLoc, 300, TEXT("BlockAll"), false, IgnoreActors,
		EDrawDebugTrace::Type::None, HitRetArray, true);

	FDamageEvent DmgEvent;

	AGuardian_Mage* pArcher = Cast<AGuardian_Mage>(GetOwner());

	float fDmg = pArcher->GetState().iDamage*GetSpellDmgRate();

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
					float fHP = Mon->TakeDamage(fDmg, DmgEvent, pArcher->GetController(), this);

					if (fHP <= 0.f)
					{
						pArcher->EraseTarget();
					}
				}

				return;
			}
		}
	}
}
