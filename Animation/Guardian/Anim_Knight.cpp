// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Knight.h"
#include "../../Character/Guardian/Guardian_Knight.h"

UAnim_Knight::UAnim_Knight()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Idle;
}

void UAnim_Knight::ChangeAnimType(EGuardianAnimType eType)
{
	AnimType = (uint8)eType;
}


void UAnim_Knight::Victory()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Victory;
}

void UAnim_Knight::Defeat()
{
	AnimType = (uint8)EGuardianAnimType::GAT_Defeat;
}

void UAnim_Knight::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Knight::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UAnim_Knight::AnimNotify_Knight_Attack()
{
	AGuardian_Knight* pOwner = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->AttackToTarget();
	}
}

void UAnim_Knight::AnimNotify_Knight_Attack_End()
{
	AGuardian_Knight* pOwner = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		PrintViewport(5.f, FColor::Red, TEXT("Archer Attack End"));
		//Archer->AttackEnable(false);
		pOwner->SetAI(EKNIGHT_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}

void UAnim_Knight::AnimNotify_Knight_Skill()
{
	AGuardian_Knight* pOwner = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->PowerStrike();
	}
}

void UAnim_Knight::AnimNotify_Knight_Skill_End()
{
	AGuardian_Knight* pOwner = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(pOwner))
	{
		pOwner->SetAI(EKNIGHT_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}
