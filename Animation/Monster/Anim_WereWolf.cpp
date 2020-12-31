// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_WereWolf.h"
#include "../../Character/Monster/Monster_WereWolf.h"


UAnim_WereWolf::UAnim_WereWolf()
{

}

void UAnim_WereWolf::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_WereWolf::Victory()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Victory;
}

void UAnim_WereWolf::Defeat()
{
}

void UAnim_WereWolf::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_WereWolf::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
