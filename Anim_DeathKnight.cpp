// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_DeathKnight.h"
#include "Monster_DeathKnight.h"

UAnim_DeathKnight::UAnim_DeathKnight()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Idle;
}

void UAnim_DeathKnight::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_DeathKnight::Victory()
{
}

void UAnim_DeathKnight::Defeat()
{
}

void UAnim_DeathKnight::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_DeathKnight::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
