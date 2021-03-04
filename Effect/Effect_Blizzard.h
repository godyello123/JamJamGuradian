// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Effect.h"
#include "Effect_Blizzard.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API AEffect_Blizzard : public AEffect
{
	GENERATED_BODY()

public:
	AEffect_Blizzard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
