// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Blizzard.h"
#include "../Character/Guardian/Guardian_Mage.h"
#include "../Character/Monster/Monster.h"


ASpell_Blizzard::ASpell_Blizzard()
{

}

void ASpell_Blizzard::SetSlowTime(float fTime)
{
	m_fSlowTime = fTime;
}

void ASpell_Blizzard::SetSlowRate(float fRate)
{
	m_fSlowRate = fRate;
}

float ASpell_Blizzard::GetSlowTime() const
{
	return m_fSlowTime;
}

float ASpell_Blizzard::GetSlowRate() const
{
	return m_fSlowRate;
}

void ASpell_Blizzard::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_Blizzard::CollisionBeginOverlap);

	SetSlowRate(0.2);
	SetSlowTime(1.5f);
	SetSpellDmgRate(0.6);

	m_fLifeTime = 0.f;
	m_fMaxLIfeTime = 5.f;

	m_fDamageTime = 0.f;
	m_fDamageMaxTime = 0.5;
}

void ASpell_Blizzard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;

	if (m_fLifeTime >= m_fMaxLIfeTime)
	{
		Destroy();
	}
}

void ASpell_Blizzard::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

			pMon->SlowEvent(m_fSlowTime, m_fSlowRate);

			float fHp = OtherActor->TakeDamage(fDmg, DmgEvent, pArcher->GetController(), this);

			if (fHp <= 0.f)
			{
				pArcher->EraseTarget();
			}
		}

		m_fDamageTime = 0.f;
	}
}
