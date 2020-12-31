// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Monster.h"
#include "Monster_Specter.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API AMonster_Specter : public AMonster
{
	GENERATED_BODY()
public:
	AMonster_Specter();

private:
	class UAnim_Specter* Animation;

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