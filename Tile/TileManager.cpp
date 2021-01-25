// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "Tile_SpawnGuardian.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	this->SetActorEnableCollision(false);
}

void ATileManager::AddTile(int32 iKey, ATile_SpawnGuardian* pTile)
{
}

ATile_SpawnGuardian* ATileManager::FindTile() const
{
	//return ATile_SpawnGuardian();
	return nullptr;
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	CreateTile();
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::CreateTile()
{
	for (int32 i = 0; i < 5; ++i)
	{
		for (int32 j = 0; j < 5; ++j)
		{
			FVector vLoc = FVector((j*150)+(j+200),(i * 150)+ (i+200), 100.f);
			FRotator vRot = FRotator::ZeroRotator;
			ATile_SpawnGuardian* pTile = GetWorld()->SpawnActor< ATile_SpawnGuardian>(vLoc, vRot);
			int32 iKey = i * 5 + j;
			AddTile(iKey, pTile);

		}
	}
}

