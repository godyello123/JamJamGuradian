// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "Tile_SpawnGuardian.h"
#include "GameFramework/Actor.h"
#include "TileManager.generated.h"

UCLASS()
class MPSG_API ATileManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileManager();

private:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<ATile_SpawnGuardian*> TileArray;

public:
	ATile_SpawnGuardian* GetTile(int32 iKey);
	int32 GetTileArraySize() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CreateTile();
	void ShowTileCount(int32 iCount);
	void CheckNearTile();



};
