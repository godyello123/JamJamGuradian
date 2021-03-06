// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DefenseGameStateBase.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FGem1
{
	GENERATED_USTRUCT_BODY()

public:
	FGem1() :
		iGoldGem(0),
		iFireGem(0),
		iIceGem(0)
	{

	}

public:
	int32 iGoldGem;
	int32 iFireGem;
	int32 iIceGem;
};


UCLASS()
class MPSG_API ADefenseGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	ADefenseGameStateBase();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FGem1 m_tGem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UMainUI* m_pMainUI;

public:
	void AllSetGem(int32 iCount);
	void AllAddGem(int32 iCount);
	void AllRemoveGem(int32 iCount);
	void AddGem(int32 iType, int32 iCount);
	void RemoveGem(int32 iType, int32 iCount);
	int32 GetGem(int32 iType) const;

public:
	void SetMainUI(class UMainUI* pUI);

};
