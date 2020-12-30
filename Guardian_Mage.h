// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Guardian.h"
#include "Guardian_Mage.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API AGuardian_Mage : public AGuardian
{
	GENERATED_BODY()

public:
	AGuardian_Mage();

public:
	virtual void LevelUP(ELevelUpType eType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);


	
};
