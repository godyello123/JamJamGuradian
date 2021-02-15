// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Guardian.h"
#include "../../Effect/Effect.h"
#include "Guardian_Warrior.generated.h"

/**
 * 
 */

UCLASS()
class MPSG_API AGuardian_Warrior : public AGuardian
{
	GENERATED_BODY()

public:
	AGuardian_Warrior();

protected:
	class UAnim_Warrior* Animation;

protected:
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AActor_Weapon* Sword;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EGUARDIAN_AI 	eAI;
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect> Effect;

public:
	void SetAI(EGUARDIAN_AI _eAI);


protected:
	void LoadSword(const FString& strSocket, const FString& strMeshPath);

public:
	void ChangeAnimation(EGuardianAnimType eType);

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
	virtual void Groggy();
	virtual void Victory();
	virtual void LevelUP(ELevelUpType eType);
	virtual void NormalLevelUp();
	virtual void FireLevelUp();
	virtual void IceLevelUp();
	virtual void Dead();
	virtual void Skill();

protected:
	virtual void Motion();
	virtual void Attack();
	virtual void SearchTarget();

public:

public:
	bool CheckDistance();
	void AttackToTarget();

public:
	void CrushAttack();

private:
	void CreateEffect();
};
