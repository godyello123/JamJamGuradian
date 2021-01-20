// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGuardianTileUI.h"
#include "Components/Button.h"

void USpawnGuardianTileUI::NativeConstruct()
{
	Super::NativeConstruct();

	KnightButton = Cast<UButton>(GetWidgetFromName(TEXT("Kngiht")));
	MageButton = Cast<UButton>(GetWidgetFromName(TEXT("Mage")));
	ArcherButton = Cast<UButton>(GetWidgetFromName(TEXT("Archer")));
	WarriorButton = Cast<UButton>(GetWidgetFromName(TEXT("Warrior")));

	KnightButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::SpawnKnight);
	MageButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::SpawnMage);
	ArcherButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::SpawnArcher);
	WarriorButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::SpawnWarrior);
}

void USpawnGuardianTileUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void USpawnGuardianTileUI::SpawnKnight()
{
	PrintViewport(2.f, FColor::Red, TEXT("KNGIHT"));
}

void USpawnGuardianTileUI::SpawnMage()
{
	PrintViewport(2.f, FColor::Red, TEXT("MAGE"));

}

void USpawnGuardianTileUI::SpawnArcher()
{
	PrintViewport(2.f, FColor::Red, TEXT("ARCHER"));

}

void USpawnGuardianTileUI::SpawnWarrior()
{
	PrintViewport(2.f, FColor::Red, TEXT("WARRIOR"));

}
