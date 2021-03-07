// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "Engine/GameInstance.h"
#include "DefenseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UDefenseGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UDefenseGameInstance();
	~UDefenseGameInstance();

private:
	int32 m_iWaveNumer;
	EGameLevel m_eGameLevel;
	int32 m_iFieldMonsterCount;
	int32 m_iMaxFieldMonsterCount;


public:
	void SetGameLevel(EGameLevel eLevel);
	EGameLevel GetGameLevel() const;

public:
	void SetWaveNumber(int32 iWave);
	int32 GetWaveNumber() const;
	void AddWaveNumber();

	void SetFieldMonsterCount(int32 iCount);
	void AddFieldMonsterCount();
	void EraseMonsterCount();

	
};
