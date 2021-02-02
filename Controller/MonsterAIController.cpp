// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Character/Monster/Monster.h"

AMonsterAIController::AMonsterAIController()
{
	GetObjectAsset(UBehaviorTree, BTAsset, "BehaviorTree'/Game/13AI/BTMonster.BTMonster'");

	if (BTAsset.Succeeded())
		m_pBTAsset = BTAsset.Object;

	GetObjectAsset(UBlackboardData, BBAsset, "BlackboardData'/Game/13AI/BBMonster.BBMonster'");

	if (BBAsset.Succeeded())
		m_pBBAsset = BBAsset.Object;
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(m_pBBAsset, Blackboard))
	{
		if (!RunBehaviorTree(m_pBTAsset))
		{

		}
	}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
