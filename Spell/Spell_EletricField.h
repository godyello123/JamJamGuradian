// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_EletricField.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_EletricField : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_EletricField();

protected:
	UPROPERTY(Category = Particle, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* particle2;


protected:
	float m_fLifeTime;
	float m_fMaxLIfeTime;
	float m_fDamageTime;
	float m_fDamageMaxTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void Damage();
	
};
