// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AnimBase.h"
#include "Anim_Knight.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Knight : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Knight();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EGuardianAnimType"))
		uint8	AnimType;

public:
	void ChangeAnimType(EGuardianAnimType eType);

public:


public:
	virtual void Victory();
	virtual void Defeat();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
		void AnimNotify_Knight_Attack();
	UFUNCTION()
		void AnimNotify_Knight_Attack_End();
	UFUNCTION()
		void AnimNotify_Knight_Skill();
	UFUNCTION()
		void AnimNotify_Knight_Skill_End();

	
};
