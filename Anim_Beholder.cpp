// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_Beholder.h"
#include "Monster_Beholder.h"


UAnim_Beholder::UAnim_Beholder()
{

}

void UAnim_Beholder::ChangeAnimType(EMonsterAnimType eType)
{
	AnimType = (uint8)eType;
}

void UAnim_Beholder::Victory()
{
	AnimType = (uint8)EMonsterAnimType::MAT_Victory;
}

void UAnim_Beholder::Defeat()
{
}

void UAnim_Beholder::AnimNotify_Beholder_Die_Start()
{
	AMonster_Beholder* Beholder = Cast<AMonster_Beholder>(TryGetPawnOwner());
	PrintViewport(1.f, FColor::Red, TEXT("Beholder_Die_Start"));
}

void UAnim_Beholder::AnimNotify_Beholder_Die_End()
{
	AMonster_Beholder* Beholder = Cast<AMonster_Beholder>(TryGetPawnOwner());

	PrintViewport(1.f, FColor::Red, TEXT("Beholder_Die_End"));
	if (Beholder)
	{
		Beholder->Destroy();
	}
}

void UAnim_Beholder::AnimNotify_Beholder_Attack()
{
	AMonster_Beholder* Beholder = Cast<AMonster_Beholder>(TryGetPawnOwner());

	if (Beholder)
	{
		Beholder->Attack();
	}
}

void UAnim_Beholder::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnim_Beholder::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
