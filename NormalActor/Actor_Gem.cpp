// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Gem.h"

// Sets default values
AActor_Gem::AActor_Gem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	//particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	//particle->SetupAttachment(Mesh);

	iValue = 0;
}

void AActor_Gem::SetValue(int32 Value)
{
	iValue = Value;
}

int32 AActor_Gem::GetValue() const
{
	return iValue;
}

// Called when the game starts or when spawned
void AActor_Gem::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActor_Gem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

