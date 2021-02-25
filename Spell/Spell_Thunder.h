// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_Thunder.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_Thunder : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_Thunder();

protected:
	float m_fLifeTime;
	float m_fLifeTimeMax;

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
