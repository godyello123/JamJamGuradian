// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Guardian.h"
#include "../../Effect/Effect.h"
#include "Guardian_Knight.generated.h"
/**
 * 
 */
UENUM(BlueprintType, Meta = (Bitflags))
enum class EKNIGHT_AI : uint8
{
	Idle,
	Attack,
	Groggy,
	Victory
};


UCLASS()
class MPSG_API AGuardian_Knight : public AGuardian
{
	GENERATED_BODY()

public:
	AGuardian_Knight();

protected:
	class UAnim_Knight* Animation;

protected:
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AActor_Weapon* Sword;
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AActor_Weapon* Shield;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EKNIGHT_AI		eAI;
	UPROPERTY(Category = Effect, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AEffect> Effect;


public:
	void SetAI(EKNIGHT_AI eAI);

public:
	void ChangeAnimation(EGuardianAnimType eType);

protected:
	void LoadSword(const FString& strSocket, const FString& strMeshPath);
	void LoadShield(const FString& strSocket, const FString& strMeshPath);

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
	virtual void LevelUP(ELevelUpType eType);
	virtual void NormalLevelUp();
	virtual void FireLevelUp();
	virtual void IceLevelUp();

protected:
	virtual void Motion();
	virtual void Attack();
	virtual void Skill();
	virtual void SearchTarget();

private:
	void CreateEffect();

public:
	virtual void Groggy();
	virtual void Victory();

public:
	bool CheckDistance();
	void AttackToTarget();
	void PowerStrike();

public:
	virtual void ShowUI(bool bShow);


	
};
