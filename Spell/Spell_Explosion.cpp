// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Explosion.h"
#include "Spell_ExplosionArrow.h"
#include "../Character/Guardian/Guardian_Archer.h"

ASpell_Explosion::ASpell_Explosion()
{
	m_fLifeTime = 0.f;
	m_fLifeTimeMax = 0.8f;
}

void ASpell_Explosion::BeginPlay()
{
	Super::BeginPlay();

	SetSpellDmgRate(0.7);
}

void ASpell_Explosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;

	if (m_fLifeTime >= m_fLifeTimeMax)
	{
		Destroy();
	}
}

void ASpell_Explosion::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FDamageEvent DmgEvent;

	ASpell_ExplosionArrow* pArrow= Cast<ASpell_ExplosionArrow>(GetOwner());

	AGuardian_Archer* pArcher = pArrow->GetArcher();


	if (IsValid(pArrow))
	{
		float fHp = OtherActor->TakeDamage(pArcher->GetState().iDamage*GetSpellDmgRate(), DmgEvent, pArcher->GetController(), this);

		if (fHp <= 0.f)
		{
			pArcher->EraseTarget();
		}

		//Destroy();
	}
	Destroy();

}
