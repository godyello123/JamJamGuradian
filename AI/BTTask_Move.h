// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Move.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UBTTask_Move : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Move();

	float fTime;
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
};
