// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseGameInstance.h"
#include "DefenseGameMode.h"


UDefenseGameInstance::UDefenseGameInstance()
{
	m_iWaveNumer = 0;
	m_iFieldMonsterCount = 0;
	m_iMaxFieldMonsterCount = 100;
}

UDefenseGameInstance::~UDefenseGameInstance()
{

}

void UDefenseGameInstance::SetGameLevel(EGameLevel eLevel)
{
	m_eGameLevel = eLevel;
}

EGameLevel UDefenseGameInstance::GetGameLevel() const
{
	return m_eGameLevel;
}

void UDefenseGameInstance::SetWaveNumber(int32 iWave)
{
	m_iWaveNumer = iWave;

	ADefenseGameMode* pMode = Cast<ADefenseGameMode>(GetWorld()->GetAuthGameMode());

	if (pMode)
	{
		pMode->GameWave(iWave);
	}
}

int32 UDefenseGameInstance::GetWaveNumber() const
{
	return m_iWaveNumer;
}

void UDefenseGameInstance::AddWaveNumber()
{
	++m_iWaveNumer;

	SetWaveNumber(m_iWaveNumer);
}

void UDefenseGameInstance::SetFieldMonsterCount(int32 iCount)
{
	m_iFieldMonsterCount = iCount;
}

void UDefenseGameInstance::AddFieldMonsterCount()
{
	++m_iFieldMonsterCount;

	//여기에 ui  나와야함
	ADefenseGameMode* pMode = Cast<ADefenseGameMode>(GetWorld()->GetAuthGameMode());

	if (pMode)
	{
		pMode->MonsterCount(m_iFieldMonsterCount);
	}

}

void UDefenseGameInstance::EraseMonsterCount()
{
	--m_iFieldMonsterCount;

	if (m_iFieldMonsterCount <= 0)
	{
		m_iFieldMonsterCount = 0;
	}
	//여기에 ui  나와야함
	ADefenseGameMode* pMode = Cast<ADefenseGameMode>(GetWorld()->GetAuthGameMode());

	if (pMode)
	{
		pMode->MonsterCount(m_iFieldMonsterCount);
	}
}
