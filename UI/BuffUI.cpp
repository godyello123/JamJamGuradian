// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffUI.h"
#include "../Character/Guardian/Guardian.h"
#include "Components/Image.h"

void UBuffUI::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	DmgBuff = Cast<UImage>(GetWidgetFromName(TEXT("DmgBuff")));
	GageBuff = Cast<UImage>(GetWidgetFromName(TEXT("GageBuff")));
}

void UBuffUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBuffUI::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


}

void UBuffUI::SetOwner(AGuardian * pOnwer)
{
	m_pOwner = pOnwer;
}

void UBuffUI::DmgBuffEnable(bool bEnable)
{
	if (bEnable)
	{
		DmgBuff->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		DmgBuff->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UBuffUI::GageBuffEnabld(bool bEnable)
{
	if (bEnable)
	{
		GageBuff->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GageBuff->SetVisibility(ESlateVisibility::Collapsed);
	}
}
