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

ATile_SpawnGuardian * ATileManager::GetTile(int32 iKey)
{
	return TileArray[iKey];
}

int32 ATileManager::GetTileArraySize() const
{
	return TileArray.Num();
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	CreateTile();
	ShowTileCount(5);
	CheckNearTile();
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
			pTile->SetTileManager(this);
			int32 iRand = FMath::RandRange(0, 2);
			int32 iNum = i * 4 + j;
			pTile->SetTileNumber(iNum);
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

void ATileManager::CheckNearTile()
{
	if (TileArray.Num()>0)
	{
		for (int32 i = 0; i < TileArray.Num(); ++i)
		{
			TileArray[i]->CheckNearTile();
		}
	}
}

