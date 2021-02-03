// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Beholder.h"
#include "../../Character/Monster/Monster_Beholder.h"



UAnim_Beholder::UAnim_Beholder()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Idle;
}

void UAnim_Beholder::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Beholder::Victory()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Victory;
}

void UAnim_Beholder::Defeat()
{
}

void UAnim_Beholder::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Beholder::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
