// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_HellCrab.h"
#include "Monster_HellCrab.h"


UAnim_HellCrab::UAnim_HellCrab()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Idle;
}

void UAnim_HellCrab::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_HellCrab::Victory()
{
}

void UAnim_HellCrab::Defeat()
{
}

void UAnim_HellCrab::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_HellCrab::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
