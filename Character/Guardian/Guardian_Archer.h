// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Guardian.h"
#include "../../Spell/Spell_MultiShot.h"
#include "../../Spell/Spell_ArcherBuff.h"
#include "../../Spell/Spell_ExplosionArrow.h"
#include "../../Spell/Spell_IceArrow.h"
#include "../../Spell/Spell_StaticArrow.h"
#include "Guardian_Archer.generated.h"

/**
 * 
 */


UCLASS()
class MPSG_API AGuardian_Archer : public AGuardian
{
	GENERATED_BODY()

public:
	AGuardian_Archer();

protected:
	class UAnim_Archer* Animation;

protected:
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AActor_Weapon* Bow;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EGUARDIAN_AI		eAI;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_MultiShot> Arrow_Red;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_MultiShot> Arrow_Yellow;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_MultiShot> Arrow_Blue;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_ExplosionArrow> ExplosionArrow;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_IceArrow> IceArrow;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_StaticArrow> StaticArrow;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_ArcherBuff> Archer_Buff;
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectile> ProjectileAsset;


private:
	bool m_bBuff;
	float m_iOriginDamage;

public:
	void BuffOn();
	void BuffOff();

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
	virtual void LevelUp(EGUARDIANLEVEL eLevel, EElementalType eType);

public:
	virtual void Dead();
	virtual void Motion();
	virtual void Attack();
	virtual void Skill();
	virtual void SearchTarget();

private:
	void Archer_Tier2(EElementalType eType);
	void Archer_Tier3(EElementalType eType);

public:
	bool CheckDistance();
	void AttackToTarget();
	void MultiShot();
	void Shot();
	void ArcherBuff();

	void Tier2Skill();

public:
	void ExplosionShot();
	void IceArrowShow();
	void StaticArrowShot();

public:
	void EraseTarget();
};
