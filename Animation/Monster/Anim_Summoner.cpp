// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Summoner.h"
#include "../../Character/Guardian/Summoner.h"

UAnim_Summoner::UAnim_Summoner()
{

}

void UAnim_Summoner::ChangeAnim(ESummonerAnimType eType)
{
	AnimType = (uint8)eType;
}

ESummonerAnimType UAnim_Summoner::GetAnimType()
{
	return (ESummonerAnimType)AnimType;
}

void UAnim_Summoner::Victory()
{
	AnimType = (uint8)ESummonerAnimType::SAT_Victory;
}

void UAnim_Summoner::Defeat()
{
	
}

void UAnim_Summoner::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Summoner::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ASummoner* pSum = Cast<ASummoner>(TryGetPawnOwner());

	if (IsValid(pSum))
	{
		UCharacterMovementComponent* pMove = pSum->GetCharacterMovement();

		if (AnimType == (uint8)ESummonerAnimType::SAT_Move)
		{
			if (pMove->Velocity.Size() > 0.f)
			{

			}
			else
			{
				AnimType = (uint8)ESummonerAnimType::SAT_Idle;
			}
		}

	}
}
