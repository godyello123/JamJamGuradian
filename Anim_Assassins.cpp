// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Assassins.h"
#include "Guardian_Assassins.h"

UAnim_Assassins::UAnim_Assassins()
{

}

void UAnim_Assassins::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Assassins::Victory()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Victory;

}

void UAnim_Assassins::Defeat()
{
}

void UAnim_Assassins::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UAnim_Assassins::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}
