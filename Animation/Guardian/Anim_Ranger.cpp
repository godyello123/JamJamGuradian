// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Ranger.h"
#include "../../Character/Guardian/Guardian_Hunter.h"

UAnim_Ranger::UAnim_Ranger()
{

}

void UAnim_Ranger::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Ranger::Victory()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Victory;
}

void UAnim_Ranger::Defeat()
{
}

void UAnim_Ranger::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Ranger::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UAnim_Ranger::AnimNotify_Mage_Skill()
{
	//스킬 발사!
	AGuardian_Hunter* pHunter = Cast<AGuardian_Hunter>(TryGetPawnOwner());

	if (IsValid(pHunter))
	{
		pHunter->Skill();
	}

}

void UAnim_Ranger::AnimNotify_Mage_Skill_End()
{
	AGuardian_Hunter* pHunter = Cast<AGuardian_Hunter>(TryGetPawnOwner());

	if (IsValid(pHunter))
	{
		pHunter->SetAI(EGUARDIAN_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}

}
