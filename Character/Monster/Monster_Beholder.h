// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Monster.h"
#include "Monster_Beholder.generated.h"

/**
 * 
 */

UCLASS()
class MPSG_API AMonster_Beholder : public AMonster
{
	GENERATED_BODY()

public:
	AMonster_Beholder();

private:
	class UAnim_Beholder* Animation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

public:
	virtual void ChangeAnim(EMonsterAnimType eType);

public:
	virtual void Skill();
	virtual void Groggy();
};
