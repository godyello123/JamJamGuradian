// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Groggy.h"
#include "../Character/Monster/Monster.h"
#include "../Controller/MonsterAIController.h"

UBTDecorator_Groggy::UBTDecorator_Groggy()
{
	NodeName = TEXT("Groggy Check");
}

bool UBTDecorator_Groggy::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (pController)
	{
		AMonster* pMonster = Cast<AMonster>(pController->GetPawn());

		if (pMonster)
		{
			if (pMonster->IsGroggy() == true)
				return true;
			else if (pMonster->IsGroggy() == false)
				return false;
		}
		else
			return false;
	}

	return false;
}
