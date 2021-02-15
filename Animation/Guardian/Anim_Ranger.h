// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AnimBase.h"
#include "Anim_Ranger.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Ranger : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Ranger();

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
		void AnimNotify_Mage_Skill();
	UFUNCTION()
		void AnimNotify_Mage_Skill_End();
	
};
