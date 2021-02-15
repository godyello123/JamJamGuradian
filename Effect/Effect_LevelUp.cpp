// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect_LevelUp.h"

AEffect_LevelUp::AEffect_LevelUp()
{
	m_fTime = 0.f;
	m_fMaxTime = 1.2f;
}

void AEffect_LevelUp::BeginPlay()
{
	Super::BeginPlay();
}

void AEffect_LevelUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fTime += DeltaTime;

	if (m_fTime <= m_fMaxTime)
	{
		Destroy();
	}
}
