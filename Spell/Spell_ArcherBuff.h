// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_ArcherBuff.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_ArcherBuff : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_ArcherBuff();

private:
	class AGuardian_Archer* Archer;

protected:
	float fLifeTime;
	float fLifeTimeMax;

public:
	void SetArcher(class AGuardian_Archer* pArcher);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
