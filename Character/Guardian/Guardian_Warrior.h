// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Guardian.h"
#include "Guardian_Warrior.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Meta = (Bitflags))
enum class EWARRIOR_AI : uint8
{
	Idle,
	Attack,
	Groggy,
	Victory
};

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
		class AActor_Weapon* TwoHandSword;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EWARRIOR_AI 	eAI;

public:
	void SetAI(EWARRIOR_AI _eAI);


protected:
	void LoadTwohandSword(const FString& strSocket, const FString& strMeshPath);

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
	void CrushAttack();
public:
	virtual void ShowUI(bool bShow);


	
};
