// Fill out your copyright notice in the Description page of Project Settings.


#include "DemonGate.h"
#include "Monster.h"
#include "Monster_Beholder.h"

// Sets default values
ADemonGate::ADemonGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Monster = nullptr;
	SpawnTime = 5.f;
	iMonsterCount = 0;
	iMaxMonsterCount = 1;
	SpawnDuration = 0.f;

	bSpawn = true;

	Target = nullptr;
}

void ADemonGate::SetMaxMonsterCount(int32 iCount)
{
	iMaxMonsterCount = iCount;
}

int32 ADemonGate::GetMaxMonsterCount() const
{
	return iMaxMonsterCount;
}

int32 ADemonGate::GetMonsterCount() const
{
	return iMonsterCount;
}

// Called when the game starts or when spawned
void ADemonGate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemonGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bSpawn)
	{
		SpawnDuration += DeltaTime;

		if (SpawnDuration >= SpawnTime)
		{
			SpawnDuration = 0.f;
			FActorSpawnParameters params;

			params.SpawnCollisionHandlingOverride =
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			FRotator Rot = FRotator(0.f, 0.f, 0.f);

			Monster = Cast<AMonster>(GetWorld()->SpawnActor<AMonster_Beholder>(GetActorLocation(), Rot, params));
			Monster->SetTarget(Target);

			for (ARoadPoint* point : RoadPointArray)
			{
				Monster->AddRoadPoint(point);
			}

			if (iMonsterCount < iMaxMonsterCount)
				++iMonsterCount;
			else
				bSpawn = false;
		}
	}
}

