// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect_CrushAttack.h"

// Sets default values
AEffect_CrushAttack::AEffect_CrushAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	particle->SetupAttachment(particle);
}

// Called when the game starts or when spawned
void AEffect_CrushAttack::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AEffect_CrushAttack::CollisionBeginOverlap);
	
}

// Called every frame
void AEffect_CrushAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffect_CrushAttack::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

