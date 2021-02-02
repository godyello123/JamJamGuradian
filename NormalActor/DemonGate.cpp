// Fill out your copyright notice in the Description page of Project Settings.


#include "DemonGate.h"
#include "../Character/Monster/Monster.h"
#include "../Character/Monster/Monster_Beholder.h"
#include "../Character/Monster/Monster_ChestImp.h"
#include "../Character/Monster/Monster_DeathKnight.h"
#include "../Character/Monster/Monster_DeathWorm.h"
#include "../Character/Monster/Monster_Demon.h"
#include "../Character/Monster/Monster_HellCrab.h"
#include "../Character/Monster/Monster_LizardMan.h"
#include "../Character/Monster/Monster_RatAssassin.h"
#include "../Character/Monster/Monster_Specter.h"
#include "../Character/Monster/Monster_WereWolf.h"
#include "../GameMode/DefenseGameMode.h"

// Sets default values
ADemonGate::ADemonGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;
	SpawnType = ESpawnMonsterType::SMT_BEHOLDER;
	SpawnTime = 5.f;
	iMonsterCount = 0;
	iMaxMonsterCount = 50;
	SpawnDuration = 0.f;

	bSpawn = true;
	bBossWave = false;

	Spline = nullptr;
	//GetClassAsset()
}

void ADemonGate::SetBossWave(bool bWave)
{
	bBossWave = bWave;
}

bool ADemonGate::IsBossWave() const
{
	return bBossWave;
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

void ADemonGate::SetSpawn(bool _bSpawn)
{
	bSpawn = _bSpawn;
}

bool ADemonGate::IsSpawn() const
{
	return bSpawn;
}

void ADemonGate::SetSpawnDurationTime(float fTime)
{
	SpawnDuration = fTime;
}

void ADemonGate::StartWave()
{
	SpawnType = (ESpawnMonsterType)FMath::RandRange(0, 7);
	
	//스테이지 10 스테이지 넘어가면 랜덤 소환
	switch (SpawnType)
	{
	case ESpawnMonsterType::SMT_BEHOLDER:
	{
		MonsterType = LoadClass<AMonster_Beholder>(nullptr, TEXT("Blueprint'/Game/02Monster/01Beholder/Beholder.Beholder_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_CHESTIMP:
	{
		MonsterType = LoadClass<AMonster_ChestImp>(nullptr, TEXT("Blueprint'/Game/02Monster/02ChestImp/ChestIMp.ChestImp_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_DEATHKNIGHT:
	{
		MonsterType = LoadClass<AMonster_DeathKnight>(nullptr, TEXT("Blueprint'/Game/02Monster/03DeathKnight/DeathKnight.DeathKnight_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_DEATHWORM:
	{
		MonsterType = LoadClass<AMonster_DeathWorm>(nullptr, TEXT("Blueprint'/Game/02Monster/04DeathWorm/DeathWorm.DeathWorm_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_DEMON:
	{
		MonsterType = LoadClass<AMonster_Demon>(nullptr, TEXT("Blueprint'/Game/02Monster/05Demon/Demon.Demon_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_HELLCRAB:
	{
		MonsterType = LoadClass<AMonster_HellCrab>(nullptr, TEXT("Blueprint'/Game/02Monster/06HellCrab/HellCrab.HellCrab_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_LIZARDMAN:
	{
		MonsterType = LoadClass<AMonster_LizardMan>(nullptr, TEXT("Blueprint'/Game/02Monster/07Lizardman/LizardMan.LizardMan_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_RATASSASSIN:
	{
		MonsterType = LoadClass<AMonster_RatAssassin>(nullptr, TEXT("Blueprint'/Game/02Monster/08RatAssassin/Rat.Rat_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_SPECTER:
	{
		MonsterType = LoadClass<AMonster_Specter>(nullptr, TEXT("Blueprint'/Game/02Monster/09Specter/Specter.Specter_C'"));
	}
	break;
	case ESpawnMonsterType::SMT_WEREWOLF:
	{
		MonsterType = LoadClass<AMonster_WereWolf>(nullptr, TEXT("Blueprint'/Game/02Monster/10WereWolf/WereWolf.WereWolf_C'"));
	}
	break;
	}
}

void ADemonGate::SpawnMonster()
{
	if (iMonsterCount >= iMaxMonsterCount)
		return;

	SpawnDuration = 0.f;

	FActorSpawnParameters params;

	params.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FRotator Rot = FRotator(0.f, 0.f, 0.f);

	AMonster* Monster= GetWorld()->SpawnActor<AMonster>(MonsterType,GetActorLocation(), Rot, params);

	Monster->SetDemonGate(this);
	Monster->SetSplice(Spline);

	for (int32 i = 0; i < PathArray.Num(); ++i)
	{
		Monster->AddPathPoint(PathArray[i]);
	}

	++iMonsterCount;
}

// Called when the game starts or when spawned
void ADemonGate::BeginPlay()
{
	Super::BeginPlay();

	ADefenseGameMode* pMode = Cast<ADefenseGameMode>(GetWorld()->GetAuthGameMode());

	if (IsValid(pMode))
		pMode->SetDemonGate(this);

	StartWave();
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
			SpawnMonster();
		}
	}
}

