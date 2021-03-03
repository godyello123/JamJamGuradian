// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_ExplosionArrow.h"
#include "Spell_RainofArrow.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_RainofArrow : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_RainofArrow();

	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_ExplosionArrow> Arrow;

protected:
	float m_fLifeTime;
	float m_fLIfeTimeMax;
	float m_fSpawnArrowTime;
	float m_fSpawnArrowTimeMax;
	int32 m_iArrowCount;
	bool m_bDestroy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void CreateArrow();

};
