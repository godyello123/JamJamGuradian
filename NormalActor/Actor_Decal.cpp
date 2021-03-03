// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Decal.h"

// Sets default values
AActor_Decal::AActor_Decal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Decal = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));

	Decal->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));

	SetRootComponent(Decal);
}

// Called when the game starts or when spawned
void AActor_Decal::BeginPlay()
{
	Super::BeginPlay();	

	//Decal->SetMa
}

// Called every frame
void AActor_Decal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AActor_Decal::SetDecalSkillOn(bool bEnable)
{
	if (bEnable)
	{
		if (m_bDecal)
		{
			m_bDecalSkillOn = true;
		}
		else
			m_bDecalSkillOn = false;
	}
	else
	{
		m_bDecal = false;
		m_bDecalSkillOn = false;
	}
}

bool AActor_Decal::GetDecalSkillOn() const
{
	return m_bDecalSkillOn;
}

void AActor_Decal::EnableDecal(bool bEnable)
{
	m_bDecal = bEnable;

	Decal->SetHiddenInGame(!m_bDecal);
}

bool AActor_Decal::IsEnableDecal() const
{
	return m_bDecal;
}

