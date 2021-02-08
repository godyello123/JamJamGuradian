// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageUpUI.h"
#include "Components/Button.h"

void UDamageUpUI::NativePreConstruct()
{
	Super::NativePreConstruct();

	FireUpButton = Cast<UButton>(GetWidgetFromName(TEXT("Normalb")));
	iceUpButton = Cast<UButton>(GetWidgetFromName(TEXT("FireUpb")));
	NormalUpButton = Cast<UButton>(GetWidgetFromName(TEXT("IceUpb")));

	NormalDmgCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_714")));
	FireDmgCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_855")));
	IceDmgCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_969")));
}

void UDamageUpUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDamageUpUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UDamageUpUI::SetFireDmgLevel(int32 iLevel)
{
}

void UDamageUpUI::SetIceDmgLevel(int32 iLevel)
{
}

void UDamageUpUI::SetNormalDmgLevel(int32 iLevel)
{
}



 