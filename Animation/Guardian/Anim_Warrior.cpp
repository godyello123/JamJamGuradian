// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Warrior.h"
#include "../../Character/Guardian/Guardian_Warrior.h"


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

void UAnim_Warrior::AnimNotify_Warrior_Attack()
{
	AGuardian_Warrior* pOwner = Cast<AGuardian_Warrior>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->AttackToTarget();
	}
}

void UAnim_Warrior::AnimNotify_Warrior_Attack_End()
{
	AGuardian_Warrior* pOwner = Cast<AGuardian_Warrior>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->SetAI(EGUARDIAN_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}

void UAnim_Warrior::AnimNotify_Knight_Skill()
{
	AGuardian_Warrior* pOwner = Cast<AGuardian_Warrior>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->Skill();
	}
}

void UAnim_Warrior::AnimNotify_Knight_Skill_End()
{
	AGuardian_Warrior* pOwner = Cast<AGuardian_Warrior>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->SetAI(EGUARDIAN_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}
