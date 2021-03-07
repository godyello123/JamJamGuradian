// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardianUI.h"
#include "../Character/Guardian/Guardian.h"
#include "../Character/Guardian/Guardian_Archer.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UGuardianUI::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UGuardianUI::NativeConstruct()
{
	Super::NativeConstruct();

	NormalLevelUpButton = Cast<UButton>(GetWidgetFromName(TEXT("Normal_LevelUp")));
	FireLevelUpButton = Cast<UButton>(GetWidgetFromName(TEXT("Fire_LevelUp")));
	IceLevelUpButton = Cast<UButton>(GetWidgetFromName(TEXT("Ice_LevelUp")));

	NormalLevelUpButton->OnClicked.AddDynamic(this, &UGuardianUI::NormalLevelUpButtonCallback);
	FireLevelUpButton->OnClicked.AddDynamic(this, &UGuardianUI::FireLevelUpButtonCallback);
	IceLevelUpButton->OnClicked.AddDynamic(this, &UGuardianUI::IceLevelUpButtonCallback);

	//m_pOwner = nullptr;
}

void UGuardianUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UGuardianUI::SetOwner(AGuardian * pOnwer)
{
	m_pOwner = pOnwer;
}

void UGuardianUI::NormalLevelUpButtonCallback()
{
	m_pOwner->LevelUp(m_pOwner->GetGuardianLevel(), EElementalType::ET_Normal);
}

void UGuardianUI::FireLevelUpButtonCallback()
{
	m_pOwner->LevelUp(m_pOwner->GetGuardianLevel(), EElementalType::ET_Fire);
}

void UGuardianUI::IceLevelUpButtonCallback()
{
	m_pOwner->LevelUp(m_pOwner->GetGuardianLevel(), EElementalType::ET_Ice);
}
