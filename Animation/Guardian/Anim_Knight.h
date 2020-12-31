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
	UFUNCTION()
	void AnimNotify_C_Knight_AT_Start();
	UFUNCTION()
	void AnimNotify_C_Knight_AT_1();
	UFUNCTION()
	void AnimNotify_C_Kngiht_AT_2();
	UFUNCTION()
	void AnimNotify_C_Knight_AT_End();
	UFUNCTION()
	void AnimNotify_Knight_AT_Start();
	UFUNCTION()
	void AnimNotify_Knight_AT();
	UFUNCTION()
	void AnimNotify_Knight_AT_End();


public:
	virtual void Victory();
	virtual void Defeat();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
