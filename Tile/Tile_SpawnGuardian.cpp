// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile_SpawnGuardian.h"

// Sets default values
ATile_SpawnGuardian::ATile_SpawnGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	bClicked = false;
	Elemental = EElementalType::ET_Normal;

}

void ATile_SpawnGuardian::Click(bool _Click)
{
	bClicked = _Click;
}

bool ATile_SpawnGuardian::IsClick() const
{
	return bClicked;
}

void ATile_SpawnGuardian::SetElementalTime(EElementalType eType)
{
	Elemental = eType;
}

EElementalType ATile_SpawnGuardian::GetElementalType() const
{
	return Elemental;
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

