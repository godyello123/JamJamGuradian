// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "../Effect/Effect_IceArrow.h"
#include "Spell_IceArrow.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_IceArrow : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_IceArrow();

protected:
	UPROPERTY(Category = Particle, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* particle1;
	UPROPERTY(Category = Particle, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* particle2;
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect_IceArrow> Effect;

private:
	class AGuardian_Archer* Archer;

protected:
	float fLifeTime;
	float fLifeTimeMax;

protected:
	float m_fSlowRate;
	float m_fSlowTime;

public:
	void SetSlowTime(float fTime);
	void SetSlowRate(float fRate);
	float GetSlowTime() const;
	float GetSlowRate() const;

public:
	void SetArcher(class AGuardian_Archer* pArcher);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CreateEffect();

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
