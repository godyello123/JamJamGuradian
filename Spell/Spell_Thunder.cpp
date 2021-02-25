// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Thunder.h"
#include "../Character/Guardian/Guardian_Mage.h"
#include "../Character/Guardian/Guardian_Mage.h"

ASpell_Thunder::ASpell_Thunder()
{

}

void ASpell_Thunder::BeginPlay()
{
	Super::BeginPlay();

	m_fLifeTime = 0.f;
	m_fLifeTimeMax = 1.f;

	SetSpellDmgRate(2.5f);
}

void ASpell_Thunder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;
	if (m_fLifeTime >= m_fLifeTimeMax)
	{
		Destroy();
	}

}

void ASpell_Thunder::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FDamageEvent DmgEvent;

	AGuardian_Mage* pArcher = Cast<AGuardian_Mage>(GetOwner());

	float fDmg = pArcher->GetState().iDamage*GetSpellDmgRate();

	if (IsValid(pArcher))
	{
		float fHp = OtherActor->TakeDamage(fDmg, DmgEvent, pArcher->GetController(), this);

		if (fHp <= 0.f)
		{
			pArcher->EraseTarget();
		}

		//CreateEffect(pArcher->GetElementalType());
	}

	Destroy();
}
