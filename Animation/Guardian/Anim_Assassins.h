// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../AnimBase.h"
#include "Anim_Assassins.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Assassins : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Assassins();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EGuardianAnimType"))
		uint8	AnimType;

public:
	void ChangeAnimType(EGuardianAnimType eType);

public:
	virtual void Victory();
	virtual void Defeat();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
