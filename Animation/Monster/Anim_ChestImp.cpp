// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_ChestImp.h"
#include "../../Character/Monster/Monster_Beholder.h"


UAnim_ChestImp::UAnim_ChestImp()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Idle;
}

void UAnim_ChestImp::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_ChestImp::Victory()
{
}

void UAnim_ChestImp::Defeat()
{
}


void UAnim_ChestImp::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_ChestImp::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
