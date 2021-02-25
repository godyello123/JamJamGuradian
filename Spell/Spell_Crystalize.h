// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_Crystalize.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_Crystalize : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_Crystalize();
protected:
	UPROPERTY(Category = Particle, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* particle1;

protected:
	float m_fLIfeTime1;
	float m_fLIfeTimeMax1;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
