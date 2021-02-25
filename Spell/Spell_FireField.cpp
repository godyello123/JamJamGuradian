// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_FireField.h"

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
}

void ASpell_FireField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;

	if (m_fLifeTime >= m_fMaxLIfeTime)
	{
		Destroy();
	}

	//m_fDamageTime += DeltaTime;

	//if (m_fDamageTime >= m_fDamageMaxTime)
	//{

	//}
}

void ASpell_FireField::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	float fDelat = GetWorld()->GetDeltaSeconds();

	m_fDamageTime += fDelat;

	if (m_fDamageTime >= m_fDamageMaxTime)
	{
		//데미지 주기

		m_fDamageTime = 0.f;
	}
}
