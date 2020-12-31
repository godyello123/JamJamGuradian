// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimBase.h"

UAnimBase::UAnimBase()
{
	bCritical = false;
}

void UAnimBase::CriticalAnim(bool _bCritical)
{
	bCritical = _bCritical;
}

void UAnimBase::Victory()
{
}

void UAnimBase::Defeat()
{
}

void UAnimBase::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnimBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
