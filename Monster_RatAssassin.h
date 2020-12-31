// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "Monster_RatAssassin.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API AMonster_RatAssassin : public AMonster
{
	GENERATED_BODY()
public:
	AMonster_RatAssassin();

private:
	class UAnim_RatAssassin* Animation;

	bool bDie;
	float fDistance;

	float fMPRecovery;

	bool bAttack;

public:
	void Die();
	bool IsDie();

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
	void Attack();
	void Move();
	void Skill();
	bool CheckTargetDistance();
	
};
