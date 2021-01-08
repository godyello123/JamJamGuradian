// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AnimBase.h"
#include "Anim_Mage.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Mage : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Mage();

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

public:
	UFUNCTION()
	void AnimNotify_Mage_MagicMissile();
	
};
