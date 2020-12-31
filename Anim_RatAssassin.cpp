// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_RatAssassin.h"
#include "Monster_RatAssassin.h"



UAnim_RatAssassin::UAnim_RatAssassin()
{

}

void UAnim_RatAssassin::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_RatAssassin::Victory()
{
}

void UAnim_RatAssassin::Defeat()
{
}

void UAnim_RatAssassin::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_RatAssassin::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
