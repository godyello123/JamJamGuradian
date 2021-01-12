// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Archer.h"
#include "../../Character/Guardian/Guardian_Archer.h"



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

void UAnim_Archer::AnimNotify_Bow_Attack_Start()
{
	AGuardian_Archer* Archer = Cast<AGuardian_Archer>(TryGetPawnOwner());

	//if (IsValid(Archer))
	//{
	//	Archer->AttackEnable(true);
	//}
}

void UAnim_Archer::AnimNotify_Bow_Attack()
{
	AGuardian_Archer* Archer = Cast<AGuardian_Archer>(TryGetPawnOwner());

	if (IsValid(Archer))
	{
		Archer->AttackToTarget();
	}
}

void UAnim_Archer::AnimNotify_Bow_Attack_End()
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
