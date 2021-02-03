// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_EasyCheck.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UBTDecorator_EasyCheck : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_EasyCheck();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	
};