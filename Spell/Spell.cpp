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

	iDamage = 0;
}

void ASpell::SetDamage(int32 iDmg)
{
	iDamage = iDmg;
}

int32 ASpell::GetDamage() const
{
	return iDamage;
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

