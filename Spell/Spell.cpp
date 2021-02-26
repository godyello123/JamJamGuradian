// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"

// Sets default values
ASpell::ASpell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;
	Collision= CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);

	particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	particle->SetupAttachment(Mesh);
	
	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));

	m_fSpellDmgRate = 0.f;

	m_bEnable = true;
}

void ASpell::SetSpellDmgRate(float fDmg)
{
	m_fSpellDmgRate = fDmg;
}

float ASpell::GetSpellDmgRate() const
{
	return m_fSpellDmgRate;
}
// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	//particle->SetRelativeLocation(FVector::ZeroVector);
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpell::EnableSkill(bool bEnable)
{
	m_bEnable = bEnable;
}

