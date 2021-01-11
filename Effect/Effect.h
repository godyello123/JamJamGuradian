// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "Effect.generated.h"

UCLASS()
class MPSG_API AEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEffect();

protected:
	UPROPERTY(Category = Particle, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* particle;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
