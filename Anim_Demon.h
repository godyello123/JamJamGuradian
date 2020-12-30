// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimBase.h"
#include "Anim_Demon.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API UAnim_Demon : public UAnimBase
{
	GENERATED_BODY()

public:
	UAnim_Demon();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "EMonsterAnimType"))
		uint8	AnimType;

public:
	void ChangeAnimType(EMonsterAnimType eType);

public:
	virtual void Victory();
	virtual void Defeat();


public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	
};
