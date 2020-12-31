// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "RoadPoint.h"
#include "GameFramework/Actor.h"
#include "DemonGate.generated.h"

UCLASS()
class MPSG_API ADemonGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADemonGate();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AMonster> SpawnType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float SpawnTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		TArray<ARoadPoint*> RoadPointArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor* Target;


	float	SpawnDuration;
	class AMonster* Monster;
	bool bSpawn;
	int32 iMonsterCount;
	int32 iMaxMonsterCount;

public:
	void SetMaxMonsterCount(int32 iCount);
	int32 GetMaxMonsterCount() const;
	int32 GetMonsterCount() const;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
