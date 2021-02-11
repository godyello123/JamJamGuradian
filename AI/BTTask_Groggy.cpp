// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Groggy.h"
#include "../Character/Monster/Monster.h"
#include "../Controller/MonsterAIController.h"

UBTTask_Groggy::UBTTask_Groggy()
{
	NodeName = (TEXT("GroggyTask"));
}

EBTNodeResult::Type UBTTask_Groggy::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type	eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_Groggy::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AMonsterAIController* pController = Cast<AMonsterAIController>(OwnerComp.GetAIOwner());

	if (pController)
	{
		AMonster* pMonster = Cast<AMonster>(pController->GetPawn());

		if (pMonster)
		{
			if (pMonster->IsDead())
				return;

			pMonster->AddCurGroggyTime(DeltaSeconds);

			if (pMonster->GetCurGroggyTime() >= pMonster->GetGroggyTime())
			{
				pMonster->GroggyEnd();
			}
		}
	}
}
