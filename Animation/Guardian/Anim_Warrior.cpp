// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Warrior.h"

UAnim_Warrior::UAnim_Warrior()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Idle;
}

void UAnim_Warrior::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Warrior::Victory()
{
}

void UAnim_Warrior::Defeat()
{
}

void UAnim_Warrior::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Warrior::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
