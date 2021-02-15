// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnGuardianTileUI.h"
#include "Components/Button.h"
#include "../Tile/Tile_SpawnGuardian.h"
#include "../Character/Guardian/Guardian_Archer.h"
#include "../Character/Guardian/Guardian_Knight.h"
#include "../Character/Guardian/Guardian_Mage.h"
#include "../Character/Guardian/Guardian_Warrior.h"

void USpawnGuardianTileUI::SetOwner(ATile_SpawnGuardian* _Owner)
{
	Owner = _Owner;
}

void USpawnGuardianTileUI::NativeConstruct()
{
	Super::NativeConstruct();

	KnightButton = Cast<UButton>(GetWidgetFromName(TEXT("KnightButton")));
	MageButton = Cast<UButton>(GetWidgetFromName(TEXT("MageButton")));
	ArcherButton = Cast<UButton>(GetWidgetFromName(TEXT("ArcherButton")));
	WarriorButton = Cast<UButton>(GetWidgetFromName(TEXT("WarriorButton")));

	KnightButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::KnightButtonCallback);
	MageButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::MageButtonCallback);
	ArcherButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::ArcherButtonCallback);
	WarriorButton->OnClicked.AddDynamic(this, &USpawnGuardianTileUI::WarriorButtonCallback);
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

void USpawnGuardianTileUI::KnightButtonCallback()
{
	PrintViewport(2.f, FColor::Red, TEXT("KNGIHT"));
	this->SetVisibility(ESlateVisibility::Collapsed);

	FVector vLoc = Owner->GetActorLocation();
	vLoc.Z += 100.f;
	FRotator vRot = Owner->GetActorRotation();
	AGuardian_Knight* Knight = GetWorld()->SpawnActor<AGuardian_Knight>(vLoc, vRot);
	
	//Owner->Click(true);
}

void USpawnGuardianTileUI::MageButtonCallback()
{
	PrintViewport(2.f, FColor::Red, TEXT("MAGE"));

	this->SetVisibility(ESlateVisibility::Collapsed);

	FVector vLoc = Owner->GetActorLocation();
	vLoc.Z += 100.f;
	FRotator vRot = Owner->GetActorRotation();
	AGuardian_Mage* Knight = GetWorld()->SpawnActor<AGuardian_Mage>(vLoc, vRot);

	//Owner->Click(true);
}

void USpawnGuardianTileUI::ArcherButtonCallback()
{
	PrintViewport(2.f, FColor::Red, TEXT("Archer"));

	this->SetVisibility(ESlateVisibility::Collapsed);

	FVector vLoc = Owner->GetActorLocation();
	vLoc.Z += 100.f;
	FRotator vRot = Owner->GetActorRotation();
	AGuardian_Archer* Knight = GetWorld()->SpawnActor<AGuardian_Archer>(vLoc, vRot);

	//Owner->Click(true);
}

void USpawnGuardianTileUI::WarriorButtonCallback()
{
	PrintViewport(2.f, FColor::Red, TEXT("Warrior"));

	this->SetVisibility(ESlateVisibility::Collapsed);

	FVector vLoc = Owner->GetActorLocation();
	vLoc.Z += 100.f;
	FRotator vRot = Owner->GetActorRotation();
	AGuardian_Warrior* pKnight = GetWorld()->SpawnActor<AGuardian_Warrior>(vLoc, vRot);

	//Owner->Click(true);
}
