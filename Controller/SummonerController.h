// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "SummonerController.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASummonerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASummonerController();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor* ClickedActor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor* RClickedActor;


private:
	bool bLButtonDown;
	bool bRButtonDown; 
	bool bGuardianSkill;
private:
	FVector vMouseHit;

public:
	void LButtonClick();
	void LButtonRelease();
	void RButtonClick();
	void RButtonRelease();

public:
	bool IsLButton() const;
	bool IsRButton() const;

protected:
	void Picking(float DeltaTime);
	void MoveSummoner(float fDeltaTime);

private:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent();

private:
	void PastProcess();
	void CurrentProcess(AActor* _Actor);

protected:
	void SkillLocation(float fDeltaTime);
	void SkillOn();
	void SkillforActor(AActor* pActor,const  FVector& vLoc);
	
};
