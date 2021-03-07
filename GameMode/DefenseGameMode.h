// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "../NormalActor/DemonGate.h"
#include "DefenseGameMode.generated.h"


/**
 * 
 */
UCLASS()
class MPSG_API ADefenseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADefenseGameMode();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ADemonGate> DemonGate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget>	MainUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UMainUI* MainUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class ASummonerController* m_pController;

private:
	class ADemonGate* m_pDemonGate;


private:
	class ATileManager* TileManager;

public:
	void SetTileManager(class ATileManager* pManager);
	class ATileManager* GetTileManager();

public:
	class UMainUI* GetMainUI() const;

public:
	void SetDemonGate(class ADemonGate* pGate);
	class ADemonGate* GetDemonGate() const;

public:
	virtual void BeginPlay();

public:
	void GameWave(int32 iWave);
	void MonsterCount(int32 iCount);
	void ClockTime(int32 iMin, int32 iSec);
	void SkipTime();
	void SpawnTile();
};
