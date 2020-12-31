// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AnimBase.h"
#include "Anim_Summoner.generated.h"


/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Summoner : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Summoner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "ESummonerAnimType"))
		uint8 AnimType;

public:
	void ChangeAnim(ESummonerAnimType eType);
	ESummonerAnimType GetAnimType();


public:
	virtual void Victory();
	virtual void Defeat();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
