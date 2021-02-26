// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_RainofArrow.h"

ASpell_RainofArrow::ASpell_RainofArrow()
{

}

void ASpell_RainofArrow::BeginPlay()
{
	Super::BeginPlay();

	m_fLifeTime = 0.f;
	m_fLIfeTimeMax = 5.f;
	m_fSpawnArrowTime = 0.f;
	m_fSpawnArrowTimeMax = 0.5;
	m_bEnable = false;
}

void ASpell_RainofArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bEnable)
	{
		m_fLifeTime += DeltaTime;
		m_fSpawnArrowTime += DeltaTime;

		if (m_fLifeTime >= m_fLIfeTimeMax)
			Destroy();
		else if (m_fSpawnArrowTime >= m_fSpawnArrowTimeMax)
			CreateArrow();
	}
}

void ASpell_RainofArrow::CreateArrow()
{
	m_fSpawnArrowTime = 0.f;
}
