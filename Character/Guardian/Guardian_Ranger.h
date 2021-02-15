// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Guardian.h"
#include "Guardian_Ranger.generated.h"

/**
 * 
 */
 

UCLASS()
class MPSG_API AGuardian_Ranger : public AGuardian
{
	GENERATED_BODY()

public:
	AGuardian_Ranger();

protected:
	class UAnim_Ranger* Animation;

protected:
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AActor_Weapon* Bow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EGUARDIAN_AI		eAI;
	//UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	TSubclassOf<ASpell_MultiShot> Arrow;
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectile> ProjectileAsset;

	EElementalType m_eElemental;

public:
	void SetElemental(EElementalType eType);

public:
	void SetAI(EGUARDIAN_AI _eAI);

protected:
	void LoadBow(const FString& strSocket, const FString& strMeshPath);

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

public:
	virtual void Motion();
	virtual void Attack();
	virtual void SearchTarget();

public:
	bool CheckDistance();
	void AttackToTarget();
	void MultiShot();

};
