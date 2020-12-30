// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Demon.h"

UAnim_Demon::UAnim_Demon()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Idle;
}

void UAnim_Demon::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Demon::Victory()
{
}

void UAnim_Demon::Defeat()
{
}

void UAnim_Demon::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Demon::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
