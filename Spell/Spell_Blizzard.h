// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_Blizzard.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_Blizzard : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_Blizzard();

protected:
	float m_fLifeTime;
	float m_fMaxLIfeTime;
	float m_fDamageTime;
	float m_fDamageMaxTime;

protected:
	float m_fSlowRate;
	float m_fSlowTime;

public:
	void SetSlowTime(float fTime);
	void SetSlowRate(float fRate);
	float GetSlowTime() const;
	float GetSlowRate() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		void CollisionBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
	
};
