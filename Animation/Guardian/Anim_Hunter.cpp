// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Hunter.h"
#include "../../Character/Guardian/Guardian_Hunter.h"

UAnim_Hunter::UAnim_Hunter()
{

}

void UAnim_Hunter::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Hunter::Victory()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Victory;
}

void UAnim_Hunter::Defeat()
{
}

void UAnim_Hunter::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Hunter::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}


void UAnim_Hunter::AnimNotify_Bow_Skill()
{
	//��ų �߻�!
	AGuardian_Hunter* pHunter = Cast<AGuardian_Hunter>(TryGetPawnOwner());

	if (IsValid(pHunter))
	{
		pHunter->Skill();
	}
}

void UAnim_Hunter::AnimNotify_Bow_Skill_End()
{
	AGuardian_Hunter* pHunter = Cast<AGuardian_Hunter>(TryGetPawnOwner());

	if (IsValid(pHunter))
	{
		pHunter->SetAI(EGUARDIAN_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}

