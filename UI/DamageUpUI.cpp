// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageUpUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../Controller/SummonerController.h"
#include "../GameMode/DefenstPlayerState.h"

void UDamageUpUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	FireUpButton = Cast<UButton>(GetWidgetFromName(TEXT("FireUpb")));
	iceUpButton = Cast<UButton>(GetWidgetFromName(TEXT("IceUpb")));
	NormalUpButton = Cast<UButton>(GetWidgetFromName(TEXT("Normalb")));

	NormalDmgCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_714")));
	FireDmgCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_855")));
	IceDmgCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_969")));

	NormalCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("NormalCost")));
	FireCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("FireCost")));
	IceCostText = Cast<UTextBlock>(GetWidgetFromName(TEXT("IceCost")));

	FireUpButton->OnClicked.AddDynamic(this, &UDamageUpUI::FireUpButtonCallback);
	iceUpButton->OnClicked.AddDynamic(this, &UDamageUpUI::IceUpButtonCallback);
	NormalUpButton->OnClicked.AddDynamic(this, &UDamageUpUI::NormalUpButtonCallback);
}

void UDamageUpUI::NativeConstruct()
{
	Super::NativeConstruct();
	FString strText = FString::Printf(TEXT("%d"), 5);
	FireCostText->SetText(FText::FromString(strText));
	IceCostText->SetText(FText::FromString(strText));
	NormalCostText->SetText(FText::FromString(strText));

}

void UDamageUpUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDamageUpUI::SetFireDmgLevelText(int32 iLevel)
{
	FString strText = FString::Printf(TEXT("Lv %d"), iLevel);
	FireDmgCount->SetText(FText::FromString(strText));
}

void UDamageUpUI::SetIceDmgLevelText(int32 iLevel)
{
	FString strText = FString::Printf(TEXT("Lv %d"), iLevel);
	IceDmgCount->SetText(FText::FromString(strText));
}

void UDamageUpUI::SetNormalDmgLevelText(int32 iLevel)
{
	FString strText = FString::Printf(TEXT("Lv %d"), iLevel);
	NormalDmgCount->SetText(FText::FromString(strText));
}

void UDamageUpUI::AddFireDmgLevel()
{
	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
}

void UDamageUpUI::AddIceDmgLevel()
{
}

void UDamageUpUI::AddNormalDmgLevel()
{
}

void UDamageUpUI::SetFireCostText(int32 iCost)
{
	FString strText = FString::Printf(TEXT("%d"), iCost);
	FireCostText->SetText(FText::FromString(strText));
}

void UDamageUpUI::SetNormalCostText(int32 iCost)
{
	FString strText = FString::Printf(TEXT("%d"), iCost);
	NormalCostText->SetText(FText::FromString(strText));
}

void UDamageUpUI::SetIceCostText(int32 iCost)
{
	FString strText = FString::Printf(TEXT("%d"), iCost);
	IceCostText->SetText(FText::FromString(strText));
}

void UDamageUpUI::FireUpButtonCallback()
{
	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();
	int32 iDmg = pState->GetFireDmg();
	int32 iCost = iDmg * 5;
	if (pState->RemoveGem(1,iCost))
	{
		pState->AddFireDmg();
		int32 iDmgLevel = pState->GetFireDmg();
		SetFireDmgLevelText(iDmgLevel);
		SetFireCostText(iDmgLevel * 5);
		//+ 되는 이펙트 ui 생성
	}
	else
	{
		//자원 부족 ui 노출
	}
}

void UDamageUpUI::IceUpButtonCallback()
{
	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();
	int32 iDmg = pState->GetIceDmg();
	int32 iCost = iDmg * 5;
	if (pState->RemoveGem(2, iCost))
	{
		pState->AddIceDmg();
		int32 iDmgLevel = pState->GetIceDmg();
		SetIceDmgLevelText(iDmgLevel);
		SetIceCostText(iDmgLevel *5);
		//+ 되는 이펙트 ui 생성
	}
	else
	{
		//자원 부족 ui 생성
	}
}

void UDamageUpUI::NormalUpButtonCallback()
{
	ASummonerController* pController = Cast<ASummonerController>(GetWorld()->GetFirstPlayerController());
	ADefenstPlayerState* pState = pController->GetPlayerState<ADefenstPlayerState>();
	int32 iDmg = pState->GetNormalDmg();
	int32 iCost = iDmg * 5;
	if (pState->RemoveGem(0, iCost))
	{
		pState->AddNormalDmg();
		int32 iDmgLevel = pState->GetNormalDmg();
		SetNormalDmgLevelText(iDmgLevel);
		SetNormalCostText(iDmgLevel * 5);
		//+ 되는 이펙트 ui 생성
	}
	else
	{
		//자원 부족 ui 생성
	}
}



 