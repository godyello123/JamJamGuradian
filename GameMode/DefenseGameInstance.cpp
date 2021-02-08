// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseGameInstance.h"

UDefenseGameInstance::UDefenseGameInstance()
{

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
}

int32 UDefenseGameInstance::GetWaveNumber() const
{
	return m_iWaveNumer;
}

void UDefenseGameInstance::AddWaveNumber()
{
	m_iWaveNumer++;
}
