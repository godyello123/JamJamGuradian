// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DefenstPlayerState.generated.h"

/**
 * 
 */
USTRUCT(Atomic, BlueprintType)
struct FGem
{
	GENERATED_USTRUCT_BODY()

public:
	FGem() :
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
class MPSG_API ADefenstPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ADefenstPlayerState();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		FGem m_tGem;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UMainUI* m_pMainUI;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iFireDmg;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iIceDmg;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		int32 m_iNormalDmg;

public:
	void AllSetGem(int32 iCount);
	void AllAddGem(int32 iCount);
	bool AllRemoveGem(int32 iCount);
	void AddGem(int32 iType, int32 iCount);
	bool RemoveGem(int32 iType, int32 iCount);
	int32 GetGem(int32 iType) const;

public:
	void AddFireDmg();
	void AddIceDmg();
	void AddNormalDmg();
	int32 GetFireDmg() const;
	int32 GetIceDmg() const;
	int32 GetNormalDmg() const;

public:
	void SetFireDmg(int32 iLevel);
	void SetIceDmg(int32 iLevel);
	void SetNormalDmg(int32 iLevel);

public:
	void SetMainUI(class UMainUI* pUI);
	
};
