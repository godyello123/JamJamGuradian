// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseGameMode.h"
#include "Summoner.h"
#include "FreeCam.h"
#include "SummonerController.h"

ADefenseGameMode::ADefenseGameMode()
{
	GetClassAsset(ASummoner, PlayerClass, "Blueprint'/Game/00Summoner/Summoner_BP.Summoner_BP_C'");

	if (PlayerClass.Succeeded())
		DefaultPawnClass = PlayerClass.Class;

	GetClassAsset(ASummonerController, PlayerController, "Blueprint'/Game/00Summoner/SummonerController_BP.SummonerController_BP_C'");

	if (PlayerController.Succeeded())
		PlayerControllerClass = PlayerController.Class;
}


void ADefenseGameMode::BeginPlay()
{
	Super::BeginPlay();
}

