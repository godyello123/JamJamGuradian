// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_MagicMissile.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_MagicMissile : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_MagicMissile();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CreateEffect();

	
};
