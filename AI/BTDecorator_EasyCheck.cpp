// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_EasyCheck.h"
#include "../GameMode/DefenseGameInstance.h"

UBTDecorator_EasyCheck::UBTDecorator_EasyCheck()
{
	NodeName = TEXT("EasyLevel");
}

bool UBTDecorator_EasyCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	UDefenseGameInstance* pInst = Cast<UDefenseGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (pInst->GetGameLevel() == EGameLevel::GL_EASY)
	{
		return true;
	}
	else
		return false;
}
