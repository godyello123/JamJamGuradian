// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Guardian.h"
#include "../../Spell/Spell_MagicMissile.h"
#include "Guardian_Mage.generated.h"


/**
 * 
 */
UENUM(BlueprintType, Meta = (Bitflags))
enum class EMAGE_AI : uint8
{
	Idle,
	Attack,
	Groggy,
	Victory
};

UCLASS()
class MPSG_API AGuardian_Mage : public AGuardian
{
	GENERATED_BODY()

public:
	AGuardian_Mage();

protected:
	class UAnim_Mage* Animation;

protected:
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AActor_Weapon* Wand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EMAGE_AI		eAI;
	UPROPERTY(Category = Spell, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ASpell_MagicMissile> MagicMissile;

public:
	void SetAI(EMAGE_AI eAI);

protected:
	void LoadWand(const FString& strSocket, const FString& strMeshPath);

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

protected:
	virtual void Motion();
	virtual void Attack();
	virtual void Skill();
	virtual void SearchTarget();

public:
	bool CheckDistance();
	void AttackToTarget();

public:
	void MagicMissaile();

public:
	virtual void ShowUI(bool bShow);



};
