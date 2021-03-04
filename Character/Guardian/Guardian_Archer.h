// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Guardian.h"
#include "../../Spell/Spell_MultiShot.h"
#include "../../Spell/Spell_ArcherBuff.h"
#include "../../Spell/Spell_ExplosionArrow.h"
#include "../../Spell/Spell_IceArrow.h"
#include "../../Spell/Spell_StaticArrow.h"
#include "../../Spell/Spell_RainofArrow.h"
#include "../../Spell/Spell_CrystalArrow.h"
#include "../../NormalActor/Actor_Decal.h"
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
		TSubclassOf<ASpell_RainofArrow> RainOfArrow;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_CrystalArrow> CrystalArrow;
	UPROPERTY(Category = Projectile, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectile> ProjectileAsset;


private:
	bool m_bTire3Skill;
	float m_iOriginDamage;

public:
	void SetAI(EGUARDIAN_AI _eAI);

private:
	void CreateDecal();

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
	virtual void Targeting(const FVector& vLoc);
	virtual void Ultimate();

private:
	void Archer_Tier2(EElementalType eType);
	void Archer_Tier3(EElementalType eType);

public:
	bool CheckDistance();
	void AttackToTarget();
	void MultiShot();
	void Shot();

public:
	void Tier2Skill();
	void ExplosionShot();
	void IceArrowShow();
	void StaticArrowShot();

public:
	void Tier3Skill();
	void RainOfArrowSkill();
	void CrystalArrowSkill();


public:
	void EraseTarget();


};
