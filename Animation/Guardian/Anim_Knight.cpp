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

void UAnim_Knight::AnimNotify_C_Knight_AT_Start()
{
	AGuardian_Knight* Knight = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(Knight))
	{
		Knight->AttackEnable(true);
		PrintViewport(1.f, FColor::Red, TEXT("AT_Start_Anim"));
	}
}

void UAnim_Knight::AnimNotify_Knight_AT_End()
{
	AGuardian_Knight* Knight = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(Knight))
	{
		Knight->AttackEnable(false);
		Knight->CheckDistance();
		PrintViewport(1.f, FColor::Red, TEXT("AT_End_Anim"));
	}
}

void UAnim_Knight::AnimNotify_Knight_AT()
{
	AGuardian_Knight* Knight = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(Knight))
	{
		Knight->AttackToTarget();
		PrintViewport(1.f, FColor::Red, TEXT("AT__Anim"));
	}
}

void UAnim_Knight::AnimNotify_Knight_AT_Start()
{
	AGuardian_Knight* Knight = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(Knight))
	{
		Knight->AttackEnable(false);
		PrintViewport(1.f, FColor::Red, TEXT("AT_Start_Anim"));
	}
}

void UAnim_Knight::AnimNotify_C_Knight_AT_End()
{
	AGuardian_Knight* Knight = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(Knight))
	{
		Knight->AttackEnable(false);
		Knight->CheckDistance();
		PrintViewport(1.f, FColor::Red, TEXT("AT_End_Anim"));
	}
}

void UAnim_Knight::AnimNotify_C_Kngiht_AT_2()
{
	AGuardian_Knight* Knight = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(Knight))
	{
		Knight->AttackToTarget();
	}
}

void UAnim_Knight::AnimNotify_C_Knight_AT_1()
{
	AGuardian_Knight* Knight = Cast<AGuardian_Knight>(TryGetPawnOwner());

	if (IsValid(Knight))
	{
		Knight->AttackToTarget();
	}
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
