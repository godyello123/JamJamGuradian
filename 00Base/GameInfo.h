// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "EngineGlobals.h"
#include "DestructibleComponent.h"
#include "Engine.h"
#include "Engine/AssetManager.h"
#include "Runtime/Engine/Classes/Engine/GameEngine.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NavigationSystem/Public/NavigationPath.h"
#include "Engine/DataTable.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
/**
 * 
 */


UENUM(BlueprintType, Meta = (Bitflags))
enum class ELevelUpType : uint8
{
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EAttackType : uint8
{
	AT_Normal,
	AT_Magic,
	AT_Holy
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EDefenseType : uint8
{
	DF_Normal,
	DF_Magic,
	DF_Demon
};


UENUM(BlueprintType, Meta = (Bitflags))
enum class EMonsterAnimType : uint8
{
	MAT_Idle,
	MAT_Move,
	MAT_Attack,
	MAT_Skill,
	MAT_Groggy,
	MAT_Victory,
	MAT_Defeat,
	MAT_Die
};

UENUM(BlueprintType, Meta = (Bitflags))
enum class EGuardianAnimType : uint8
{
	GAT_Idle,
	GAT_Move,
	GAT_Attack,
	GAT_Skill,
	GAT_Groggy,
	GAT_Victory,
	GAT_Defeat
};


UENUM(BlueprintType,Meta=(Bitflags))
enum class ESummonerAnimType : uint8
{
	SAT_Idle,
	SAT_Move,
	SAT_Attack,
	SAT_Summon,
	SAT_Groggy,
	SAT_Victory

};

DECLARE_LOG_CATEGORY_EXTERN(UE7, Log, All);
#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("{") + FString::FromInt(__LINE__) + TEXT("}"))
#define	LOG(Format, ...)	UE_LOG(UE7, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

void PrintViewport(float fTime, const FColor& Color,
	const FString& strText);

#define TICKON PrimaryActorTick.bCanEverTick = true
#define TICKOFF PrimaryActorTick.bCanEverTick = false

#define GetObjectAsset(ClassType,Return,Path) static ConstructorHelpers::FObjectFinder<ClassType>	Return(TEXT(Path))
#define GetClassAsset(ClassType,Return,Path) static ConstructorHelpers::FClassFinder<ClassType>	Return(TEXT(Path))

#define FreeCamLocationOffsetX -500.f
#define FreeCamLocationOffsetY 0.f
#define FreeCamLocationOffsetZ 1200.f

#define FreeCamRotationOffsetRoll 0.f
#define FreeCamRotationOffsetYaw 0.f
#define FreeCamRotationOffsecPitch -60.f
