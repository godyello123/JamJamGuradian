// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Lizardman.h"
#include "Monster_LizardMan.h"


UAnim_Lizardman::UAnim_Lizardman()
{

}

void UAnim_Lizardman::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Lizardman::Victory()
{
}

void UAnim_Lizardman::Defeat()
{
}

void UAnim_Lizardman::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Lizardman::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
