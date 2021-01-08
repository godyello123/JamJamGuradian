// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Mage.h"
#include "../../Character/Guardian/Guardian_Mage.h"

UAnim_Mage::UAnim_Mage()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Idle;
}

void UAnim_Mage::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Mage::Victory()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Victory;
}

void UAnim_Mage::Defeat()
{
}

void UAnim_Mage::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Mage::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UAnim_Mage::AnimNotify_Mage_MagicMissile()
{
	AGuardian_Mage* Knight = Cast<AGuardian_Mage>(TryGetPawnOwner());

	if (IsValid(Knight))
		Knight->MagicMissaile();
}
