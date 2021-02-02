// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "DemonGate.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class ESpawnMonsterType : uint8
{
	SMT_BEHOLDER,
	SMT_CHESTIMP,
	SMT_DEATHKNIGHT,
	SMT_DEATHWORM,
	SMT_DEMON,
	SMT_HELLCRAB,
	SMT_LIZARDMAN,
	SMT_RATASSASSIN,
	SMT_SPECTER,
	SMT_WEREWOLF
};

UCLASS()
class MPSG_API ADemonGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADemonGate();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		ESpawnMonsterType SpawnType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float SpawnTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> PathArray;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Meta=(AllowPrivateAccess="true"))
		float	SpawnDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess="true"))
		int32 iMonsterCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess="true"))
		int32 iMaxMonsterCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bBossWave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor_Spline* Spline;

private:
	UPROPERTY(Category = Monster, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMonster> MonsterType;


public:
	void SetBossWave(bool bWave);
	bool IsBossWave() const;

public:
	void SetMaxMonsterCount(int32 iCount);
	int32 GetMaxMonsterCount() const;
	int32 GetMonsterCount() const;

public:
	void SetSpawn(bool bSpawn);
	bool IsSpawn() const;

public:
	void SetSpawnDurationTime(float fTime);

public:
	void StartWave();
	void SpawnMonster();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
