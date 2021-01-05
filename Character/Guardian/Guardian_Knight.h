// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Guardian.h"
#include "Guardian_Knight.generated.h"

/**
 * 
 */
UENUM(BlueprintType, Meta = (Bitflags))
enum class EKngihtAI : uint8
{
	Knight_Idle,
	Knight_Attack,
	Knight_Groggy,
	Skill
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bAttack;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EKngihtAI		eAI;

public:
	void AttackEnable(bool bEnable);
	bool IsAttack() const;

public:
	virtual void LevelUP(ELevelUpType eType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

private:
	void Attack();
	void SearchTarget();

public:
	bool CheckDistance();

public:
	void  AttackToTarget();

	
};
