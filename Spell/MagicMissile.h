// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "MagicMissile.generated.h"

UCLASS()
class MPSG_API AMagicMissile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicMissile();

protected:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
	UPROPERTY(Category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* particle;
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* Movement;

protected:
	int32 iDamage;

public:
	void SetDamage(int32 iDmg);
	int32 GetDamage() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void CreateEffect();

};
