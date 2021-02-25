// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "DefenseGameMode.generated.h"
//#include "../NormalActor/DemonGate.h"

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
	class ADemonGate* DemonGate;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget>	MainUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UMainUI* MainUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class ASummonerController* m_pController;

public:
	class UMainUI* GetMainUI() const;



public:
	void SetDemonGate(class ADemonGate* pGate);
	class ADemonGate* GetDemonGate() const;

public:
	virtual void BeginPlay();
	
};
