// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Groggy.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UBTTask_Groggy : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_Groggy();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	
};
