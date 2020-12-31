// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "Animation/AnimInstance.h"
#include "AnimBase.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnimBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAnimBase();	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool bCritical;

public:
	void CriticalAnim(bool _bCritical);

public:
	virtual void Victory();
	virtual void Defeat();

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
};
