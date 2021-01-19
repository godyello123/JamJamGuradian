// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile_SpawnGuardian.h"
#include "../Character/Guardian/Guardian_Archer.h"
#include "../Character/Guardian/Guardian_Knight.h"
#include "../Character/Guardian/Guardian_Mage.h"
#include "../Character/Guardian/Guardian_Warrior.h"


// Sets default values
ATile_SpawnGuardian::ATile_SpawnGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	bClicked = false;
	Elemental = EElementalType::ET_Normal;

	Tags.Add("Tile");

}

void ATile_SpawnGuardian::Click(bool _Click)
{
	bClicked = _Click;
}

bool ATile_SpawnGuardian::IsClick() const
{
	return bClicked;
}

void ATile_SpawnGuardian::SetElementalType(EElementalType eType)
{
	Elemental = eType;
}

EElementalType ATile_SpawnGuardian::GetElementalType() const
{
	return Elemental;
}

void ATile_SpawnGuardian::SpawnGuardian(EGuardianType eType)
{
	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();

	switch (eType)
	{
	case EGuardianType::GT_KNIGHT:
	{
		AGuardian_Knight* pKnight = GetWorld()->SpawnActor<AGuardian_Knight>(vLoc, vRot);
	}
	break;
	case EGuardianType::GT_MAGE:
	{
		AGuardian_Mage* pMage = GetWorld()->SpawnActor<AGuardian_Mage>(vLoc, vRot);
	}
	break;
	case EGuardianType::GT_WARRIOR:
	{
		AGuardian_Warrior* pWarrior = GetWorld()->SpawnActor<AGuardian_Warrior>(vLoc, vRot);
	}
	break;
	case EGuardianType::GT_ARCHER:
	{
		AGuardian_Archer* pArcher = GetWorld()->SpawnActor<AGuardian_Archer>(vLoc, vRot);
	}
		break;
	}

	SetElementalType(EElementalType::ET_Normal);
}

// Called when the game starts or when spawned
void ATile_SpawnGuardian::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile_SpawnGuardian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile_SpawnGuardian::ShowUI(bool bShow)
{
	if (bShow)
	{
		PrintViewport(2.f, FColor::Yellow, TEXT("SHOW UI"));
	}
	else
	{
		PrintViewport(2.f, FColor::Yellow, TEXT("HIDE UI"));
	}
	
}

