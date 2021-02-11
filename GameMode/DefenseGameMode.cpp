// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseGameMode.h"
#include "DefenseGameStateBase.h"
#include "DefenstPlayerState.h"
#include "../Controller/SummonerController.h"
#include "../Character/Guardian/Summoner.h"
#include "../Character/Guardian/FreeCam.h"
#include "../NormalActor/DemonGate.h"
#include "../UI/MainUI.h"

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
}


UMainUI* ADefenseGameMode::GetMainUI() const
{
	return MainUI;
}

void ADefenseGameMode::SetDemonGate(ADemonGate* pGate)
{
	if(pGate)
		DemonGate = pGate;
}

ADemonGate* ADefenseGameMode::GetDemonGate() const
{
	return DemonGate;
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
}

