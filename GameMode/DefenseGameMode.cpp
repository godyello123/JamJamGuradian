// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseGameMode.h"
#include "DefenseGameStateBase.h"
#include "DefenstPlayerState.h"
#include "../Controller/SummonerController.h"
#include "../Character/Guardian/Summoner.h"
#include "../Character/Guardian/FreeCam.h"
#include "../NormalActor/DemonGate.h"
#include "../UI/MainUI.h"
#include "../Tile/TileManager.h"

ADefenseGameMode::ADefenseGameMode()
{
	GetClassAsset(ASummoner, PlayerClass, "Blueprint'/Game/00Summoner/Summoner_BP.Summoner_BP_C'");

	if (PlayerClass.Succeeded())
		DefaultPawnClass = PlayerClass.Class;

	GetClassAsset(ASummonerController, PlayerController, "Blueprint'/Game/00Summoner/SummonerController_BP.SummonerController_BP_C'");

	if (PlayerController.Succeeded())
		PlayerControllerClass = PlayerController.Class;

	GetClassAsset(UMainUI, MainUIAsset, "WidgetBlueprint'/Game/10UI/Main_UI.Main_UI_C'");

	if (MainUIAsset.Succeeded())
		MainUIClass = MainUIAsset.Class;

	GetClassAsset(ADemonGate, DemonGateAsset, "Blueprint'/Game/02Monster/DemonG.DemonG_C'");

	if (DemonGateAsset.Succeeded())
		DemonGate = DemonGateAsset.Class;
}


void ADefenseGameMode::SetTileManager(ATileManager * pManager)
{
	TileManager = pManager;
}

ATileManager * ADefenseGameMode::GetTileManager()
{
	return TileManager;
}

UMainUI* ADefenseGameMode::GetMainUI() const
{
	return MainUI;
}

void ADefenseGameMode::SetDemonGate(ADemonGate* pGate)
{
	if(pGate)
		m_pDemonGate = pGate;
}

ADemonGate* ADefenseGameMode::GetDemonGate() const
{
	return m_pDemonGate;
}

void ADefenseGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(MainUIClass))
	{
		MainUI = Cast<UMainUI>(CreateWidget(GetWorld(), MainUIClass));

		if (MainUI)
		{
			MainUI->AddToViewport();
			MainUI->SetWaveNumber(1);
			ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());

			ADefenstPlayerState* pPlayerState = pController->GetPlayerState<ADefenstPlayerState>();

			if (pPlayerState)
			{
				pPlayerState->SetMainUI(MainUI);
				pPlayerState->AllSetGem(5);
				pPlayerState->SetFireDmg(1);
				pPlayerState->SetIceDmg(1);
				pPlayerState->SetNormalDmg(1);
			}
		}
	}

	TileManager = GetWorld()->SpawnActor<ATileManager>();
}

void ADefenseGameMode::GameWave(int32 iWave)
{
	if (MainUI)
	{
		MainUI->SetWaveNumber(iWave);
	}
}

void ADefenseGameMode::MonsterCount(int32 iCount)
{
	if (MainUI)
	{
		MainUI->SetMonsterCountText(iCount);
	}
}

void ADefenseGameMode::ClockTime(int32 iMin, int32 iSec)
{
	if (MainUI)
	{
		MainUI->SetClock(iMin, iSec);
	}
}

void ADefenseGameMode::SkipTime()
{
	if (m_pDemonGate)
	{
		if(!m_pDemonGate->IsSpawn())
			m_pDemonGate->StartWave();
	}
}

void ADefenseGameMode::SpawnTile()
{
	TileManager->ShowTile();
}

