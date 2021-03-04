// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_FireField.h"
#include "../Character/Guardian/Guardian_Mage.h"
#include "../Character/Monster/Monster.h"

ASpell_FireField::ASpell_FireField()
{
	m_fLifeTime = 0.f;
	m_fMaxLIfeTime = 5.f;

	m_fDamageTime = 0.f;
	m_fDamageMaxTime = 0.5;


	particle2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle2"));
	particle2->SetupAttachment(Mesh);
	particle3 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle3"));
	particle3->SetupAttachment(Mesh);
	particle4 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle4"));
	particle4->SetupAttachment(Mesh);
}

void ASpell_FireField::BeginPlay()
{
	Super::BeginPlay();

	Collision->SetEnableGravity(false);
	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_FireField::CollisionBeginOverlap);

	SetSpellDmgRate(0.5);
}

void ASpell_FireField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;

	if (m_fLifeTime >= m_fMaxLIfeTime)
	{
		Destroy();
	}
}

void ASpell_FireField::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	float fDelat = GetWorld()->GetDeltaSeconds();

	m_fDamageTime += fDelat;

	if (m_fDamageTime >= m_fDamageMaxTime)
	{
		//데미지 주기
		FDamageEvent DmgEvent;

		AGuardian_Mage* pArcher = Cast<AGuardian_Mage>(GetOwner());

		float fDmg = pArcher->GetState().iDamage*GetSpellDmgRate();

		if (IsValid(pArcher))
		{
			AMonster* pMon = Cast<AMonster>(OtherActor);

			float fHp = OtherActor->TakeDamage(fDmg, DmgEvent, pArcher->GetController(), this);

			if (fHp <= 0.f)
			{
				pArcher->EraseTarget();
			}
		}

		m_fDamageTime = 0.f;
	}
}
