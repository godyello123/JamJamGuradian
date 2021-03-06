// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Move.h"
#include "../NormalActor/Actor_Spline.h"
#include "../Character/Monster/Monster.h"
#include "../Controller/MonsterAIController.h"

UBTTask_Move::UBTTask_Move()
{
	NodeName = TEXT("SplineMove");
	bNotifyTick = true;
	fTime = 0.f;
}

EBTNodeResult::Type UBTTask_Move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type	eResult = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_Move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

			if (pMonster->IsGroggy())
				return;

			if (pMonster->IsGroggy() == false)
			{
				pMonster->AddSplineTime(DeltaSeconds);

				AActor_Spline* pSpline = pMonster->GetSpline();

				pMonster->ChangeAnim(EMonsterAnimType::MAT_Move);

				if (pSpline)
				{
					FVector vSpline = pSpline->GetPathLocation(pMonster->GetSplineTime());

					pController->MoveToLocation(vSpline, -1.f, false, true);

					//pMonster->SetActorLocation(vSpline);

					float fDuration = pSpline->GetSplineDurationTime();

					if (pMonster->GetSplineTime() >= fDuration)
						pMonster->ClearSplineTime();
				}

			}
		}
	}
}
