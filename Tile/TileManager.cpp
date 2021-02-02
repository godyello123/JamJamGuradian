// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"
#include "Tile_SpawnGuardian.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	this->SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	CreateTile();
	ShowTileCount(5);

}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileManager::CreateTile()
{
	for (int32 i = 0; i < 8; ++i)
	{
		for (int32 j = 0; j < 4; ++j)
		{
			FVector vLoc = FVector((j*170),(i * 170), 20.f);
			FRotator vRot = FRotator::ZeroRotator;
			ATile_SpawnGuardian* pTile = GetWorld()->SpawnActor< ATile_SpawnGuardian>(vLoc, vRot);
			pTile->EnableTile(false);
			TileArray.Add(pTile);
		}
	}
}

void ATileManager::ShowTileCount(int32 iCount)
{
	if (iCount > 0 && iCount < 25)
	{
		for (int32 i = 0; i < iCount;)
		{
			int32 iKey = FMath::RandRange(0, 24);

			if (!TileArray[iKey]->IsShow())
			{
				TileArray[iKey]->EnableTile(true);
				++i;
			}
		}
	}
}

