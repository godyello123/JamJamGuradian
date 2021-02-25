// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "Spell_Explosion.h"
#include "Spell_ExplosionArrow.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_ExplosionArrow : public ASpell
{
	GENERATED_BODY()


public:
	ASpell_ExplosionArrow();


	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_Explosion> ExplosionAsset;
	
protected:
	class AGuardian_Archer* m_pArcher;

public:
	AGuardian_Archer* GetArcher() const;

protected:
	float m_fLifeTime;
	float m_fLifeTimeMax;
	FVector m_vPos;

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
	void CreateExplosion();

};
