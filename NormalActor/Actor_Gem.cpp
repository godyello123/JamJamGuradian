// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Gem.h"
#include "../GameMode/DefenseGameMode.h"
#include "../GameMode/DefenseGameStateBase.h"
#include "../Character/Guardian/Summoner.h"

// Sets default values
AActor_Gem::AActor_Gem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	//particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	//particle->SetupAttachment(Mesh);

	m_iGemCount = 0;
	m_fLifeTime = 0.f;
	m_fMaxLifeTime = 1.5;
}

void AActor_Gem::SetGemCount(int32 Value)
{
	m_iGemCount = Value;
}

int32 AActor_Gem::GetGemCount() const
{
	return m_iGemCount;
}

void AActor_Gem::SetElementalType(int32 iType)
{
	Type = iType;
}

int32 AActor_Gem::GetElementalType() const
{
	return Type;
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

	m_fLifeTime += DeltaTime;

	if (m_fLifeTime > m_fMaxLifeTime)
	{
		ADefenseGameMode* pMode = Cast<ADefenseGameMode>(GetWorld()->GetAuthGameMode());

		if (pMode)
		{
			ADefenseGameStateBase* pBase = pMode->GetGameState<ADefenseGameStateBase>();
			pBase->AddGem(Type, m_iGemCount);
		}

		Destroy();
	}

}

