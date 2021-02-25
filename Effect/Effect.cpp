// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect.h"

// Sets default values
AEffect::AEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	SetRootComponent(particle);

}

// Called when the game starts or when spawned
void AEffect::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fLifeTime += DeltaTime;

	if (m_fLifeTime >= 2.f)
	{
		Destroy();
	}
}

