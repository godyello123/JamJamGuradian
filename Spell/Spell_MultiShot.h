// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "../Effect/Effect_Multishot.h"
#include "Spell_MultiShot.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_MultiShot : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_MultiShot();

protected:
protected:
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect_Multishot> Effect;

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
