// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Spell.h"
#include "../Effect/Effect_Static.h"
#include "Spell_StaticArrow.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ASpell_StaticArrow : public ASpell
{
	GENERATED_BODY()
	
public:
	ASpell_StaticArrow();

protected:
	float fLifeTime;
	float fLifeTimeMax;

protected:
	int32 m_iTargetCount;
	int32 m_iTargetCountMax;

public:
	void SetTargetCount(int32 iCount);
	int32 GetTargetCount() const;
	void SetTargetCountMax(int32 iCount);
	int32 GetTargetCountMax() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor* Target;
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect_Static> Effect_Static;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	bool Check();
	void CreateEffect();
	void CreateStatic();

public:
	UFUNCTION()
		void CollisionBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	//UFUNCTION()
	//	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, 
	//		class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, 
	//		FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);
};
