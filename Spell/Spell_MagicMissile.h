// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "../Effect/Effect_MagicMissile.h"
#include "Spell_MagicMissile.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_MagicMissile : public ASpell
{
	GENERATED_BODY()

public:
	ASpell_MagicMissile();

protected:
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEffect_MagicMissile> Effect_Yellow;
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect_MagicMissile> Effect_Red;
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect_MagicMissile> Effect_Blue;

//private:
	//class AGuardian_Mage* Mage;

public:
	void SetMage(class AGuardian_Mage* pMage);

protected:
	float fLifeTime;
	float fLifeTimeMax;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CreateEffect(EElementalType eType);

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
