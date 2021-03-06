// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "../Effect/Effect_LevelUp.h"
#include "Blueprint/UserWidget.h"
#include "Tile_SpawnGuardian.generated.h"

UCLASS()
class MPSG_API ATile_SpawnGuardian : public AActor
{
	GENERATED_BODY()
	
public:
	ATile_SpawnGuardian();

public:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
	UPROPERTY(Category = Type, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EElementalType Elemental;
	UPROPERTY(Category=Effect,VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
		TSubclassOf<AEffect_LevelUp> Spawn_EffectAsset;

private:
	class AGuardian* m_pGuardian;
	class ATileManager* m_pTileManager;
	int32 m_iTileNumber;
	TArray<ATile_SpawnGuardian*> m_NearTileArray;

public:
	void SetTileManager(class ATileManager* pManager);
	class ATileManager* GetTileManager() const;

public:
	void AddTile(ATile_SpawnGuardian* pTile);
	ATile_SpawnGuardian* GetNearTile(int32 iKey);
	int32 GetNearTileArraySize() const;

public:
	void SetTileNumber(int32 iNum);
	int32 GetTileNumbet() const;

public:
	void SetGuardian(class AGuardian* pGuardian);
	class AGuardian* GetGuardian() const;

private:
	bool bShowTile;

public:
	bool IsShow();

public:
	void SetElementalType(EElementalType eType);
	EElementalType GetElementalType() const;


public:
	void SpawnGuardian(int32 iType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void EnableTile(bool bEnable);

public:
	void CheckNearTile();
};
