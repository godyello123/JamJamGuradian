// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Crystalize.h"


ASpell_Crystalize::ASpell_Crystalize()
{
	particle1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle1"));
	particle1->SetupAttachment(Mesh);
}

void ASpell_Crystalize::BeginPlay()
{
	Super::BeginPlay();

	m_fLIfeTime1 = 0.f;

	m_fLIfeTimeMax1 = 2;
}

void ASpell_Crystalize::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLIfeTime1 += DeltaTime;

	if (m_fLIfeTime1 >= m_fLIfeTimeMax1)
	{
		Destroy();
	}
}
