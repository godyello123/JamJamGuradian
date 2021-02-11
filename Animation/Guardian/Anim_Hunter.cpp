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

void UAnim_Hunter::AnimNotify_Hunter_Attack_Start()
{
	AGuardian_Archer* Archer = Cast<AGuardian_Archer>(TryGetPawnOwner());
}

void UAnim_Hunter::AnimNotify_Hunter_Attack()
{
	AGuardian_Archer* Archer = Cast<AGuardian_Archer>(TryGetPawnOwner());

	if (IsValid(Archer))
	{
		Archer->AttackToTarget();
	}
}

void UAnim_Hunter::AnimNotify_Hunter_Attack_End()
{
	AGuardian_Archer* Archer = Cast<AGuardian_Archer>(TryGetPawnOwner());

	if (IsValid(Archer))
	{
		PrintViewport(5.f, FColor::Red, TEXT("Archer Attack End"));
		//Archer->AttackEnable(false);
		Archer->SetAI(EARCHER_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}

void UAnim_Hunter::AnimNotify_Hunter_Skill()
{
	//스킬 발사!
	AGuardian_Archer* Archer = Cast<AGuardian_Archer>(TryGetPawnOwner());

	if (IsValid(Archer))
	{
		Archer->MultiShot();
	}
}

void UAnim_Hunter::AnimNotify_Hunter_Skill_End()
{
	AGuardian_Archer* Archer = Cast<AGuardian_Archer>(TryGetPawnOwner());

	if (IsValid(Archer))
	{
		Archer->SetAI(EARCHER_AI::Idle);
		AnimType = (uint8)EGuardianAnimType::GAT_Idle;
	}
}
