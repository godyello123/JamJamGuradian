// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "../Effect/Effect_Crystal.h"
#include "Spell_CrystalArrow.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_CrystalArrow : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_CrystalArrow();

protected:
	UPROPERTY(Category = Particle, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* particle1;
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect_Crystal> EffectAsset;

protected:
	float m_fLifeTime;
	float m_fLifeTimeMax;
	FVector m_vPos;

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


public:
	void CreateEffect();

};
