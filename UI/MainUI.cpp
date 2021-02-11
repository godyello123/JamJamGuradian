// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "../GameMode/DefenseGameInstance.h"
#include "../GameMode/DefenseGameMode.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DamageUpUI.h"
#include "Components/Button.h"


void UMainUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	WaveText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Wave")));

	WaveNumberText = Cast<UTextBlock>(GetWidgetFromName(TEXT("WaveNumber")));

	GoldGemCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("GoldGemCount")));

	FireGemCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("FireGemCount")));

	IceGemCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("IceGemCount")));

	GoldGemImage = Cast<UImage>(GetWidgetFromName(TEXT("GoldGem")));
	FireGemImage = Cast<UImage>(GetWidgetFromName(TEXT("FireGem")));
	IceGemImage = Cast<UImage>(GetWidgetFromName(TEXT("IceGem")));

	DamageUpButton = Cast<UButton>(GetWidgetFromName(TEXT("DamageUp")));
	UtilityUpButton = Cast<UButton>(GetWidgetFromName(TEXT("UtilityUp")));

	DamageUpButton->OnClicked.AddDynamic(this, &UMainUI::DamageUpCallback);
	DamageUpUI = Cast<UDamageUpUI>(GetWidgetFromName(TEXT("DmgUI")));


	//DamageUpUI->SetVisibility(ESlateVisibility::Collapsed);
}

void UMainUI::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UMainUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainUI::SetWaveNumber(int32 iWave)
{
	FString	strText = FString::Printf(TEXT("%d"), iWave);
	WaveNumberText->SetText(FText::FromString(strText));
}

void UMainUI::SetIceGemCount(int32 iCount)
{
	FString strText = FString::Printf(TEXT("%d"), iCount);
	if(IceGemCountText)
		IceGemCountText->SetText(FText::FromString(strText));
}

void UMainUI::SetGoldGemCount(int32 iCount)
{
	FString strText = FString::Printf(TEXT("%d"), iCount);
	if(GoldGemCountText)
		GoldGemCountText->SetText(FText::FromString(strText));
}

void UMainUI::SetFireGemCount(int32 iCount)
{
	FString strText = FString::Printf(TEXT("%d"), iCount);
	if(FireGemCountText)
		FireGemCountText->SetText(FText::FromString(strText));
}

void UMainUI::DamageUpCallback()
{
	switch (DamageUpUI->GetVisibility())
	{
	case ESlateVisibility::Visible:
		DamageUpUI->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::Collapsed:
		DamageUpUI->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void UMainUI::SetFireDmgLevel(int32 iLevel)
{
	if (DamageUpUI->GetVisibility() == ESlateVisibility::Visible)
		DamageUpUI->SetFireDmgLevelText(iLevel);
}

void UMainUI::SetIceDmgLevel(int32 iLevel)
{
	if (DamageUpUI->GetVisibility() == ESlateVisibility::Visible)
		DamageUpUI->SetIceDmgLevelText(iLevel);
}

void UMainUI::SetNormalDmgLevel(int32 iLevel)
{
	if (DamageUpUI->GetVisibility() == ESlateVisibility::Visible)
		DamageUpUI->SetNormalDmgLevelText(iLevel);
}
