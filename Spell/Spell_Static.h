// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_Static.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_Static : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_Static();

protected:
	int32 m_iTargetCount;

public:
	void SetTargetCount(int32 iCount);
	int32 GetTargetCount() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
