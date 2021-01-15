// Fill out your copyright notice in the Description page of Project Settings.


#include "TileManager.h"

// Sets default values
ATileManager::ATileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;
}

void ATileManager::AddTile(int32 iKey, Tile_SpawnGuardian pTile)
{
}

Tile_SpawnGuardian ATileManager::FindTile() const
{
	return Tile_SpawnGuardian();
}

// Called when the game starts or when spawned
void ATileManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

