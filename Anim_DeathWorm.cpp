// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_DeathWorm.h"
#include "Monster_DeathWorm.h"

UAnim_DeathWorm::UAnim_DeathWorm()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Idle;
}

void UAnim_DeathWorm::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_DeathWorm::Victory()
{
}

void UAnim_DeathWorm::Defeat()
{
}

void UAnim_DeathWorm::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_DeathWorm::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
