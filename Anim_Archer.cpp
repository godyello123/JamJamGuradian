// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Archer.h"
#include "Guardian_Archer.h"


UAnim_Archer::UAnim_Archer()
{

}

void UAnim_Archer::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Archer::Victory()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Victory;
}

void UAnim_Archer::Defeat()
{
}

void UAnim_Archer::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Archer::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
