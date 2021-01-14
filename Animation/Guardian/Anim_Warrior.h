// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../AnimBase.h"
#include "Anim_Warrior.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Warrior : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Warrior();

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
		void AnimNotify_Warrior_Attack();
	UFUNCTION()
		void AnimNotify_Warrior_Attack_End();
	UFUNCTION()
		void AnimNotify_Warrior_Skill();
	UFUNCTION()
		void AnimNotify_Warrior_Skill_End();
};
