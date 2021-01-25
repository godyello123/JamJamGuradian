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
	TMap<int32, ATile_SpawnGuardian*> TileMap;

public:
	void AddTile(int32 iKey, ATile_SpawnGuardian* pTile);
	class ATile_SpawnGuardian* FindTile() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CreateTile();



};
