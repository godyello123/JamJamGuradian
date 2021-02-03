// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "../AnimBase.h"
#include "Anim_Lizardman.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Lizardman : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Lizardman();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EMonsterAnimType"))
		uint8	AnimType;

public:
	void ChangeAnimType(EMonsterAnimType eType);

public:
	virtual void Victory();
	virtual void Defeat();



public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
