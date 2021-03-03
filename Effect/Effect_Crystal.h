// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effect.h"
#include "Effect_Crystal.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API AEffect_Crystal : public AEffect
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEffect_Crystal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
