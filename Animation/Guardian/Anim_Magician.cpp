// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Magician.h"
#include "../../Character/Guardian/Guardian_Magician.h"

UAnim_Magician::UAnim_Magician()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Idle;
}

void UAnim_Magician::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Magician::Victory()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Victory;
}

void UAnim_Magician::Defeat()
{
}

void UAnim_Magician::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Magician::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UAnim_Magician::AnimNotify_Mage_Skill()
{
	AGuardian_Magician* pOwner = Cast<AGuardian_Magician>(TryGetPawnOwner());

	if (IsValid(pOwner))
		pOwner->Skill();
}

void UAnim_Magician::AnimNotify_Mage_Skill_End()
{
	AGuardian_Magician* pOwner = Cast<AGuardian_Magician>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->SetAI(EGUARDIAN_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}
