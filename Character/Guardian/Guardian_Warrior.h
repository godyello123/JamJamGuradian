// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Guardian.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bAttack;
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class AActor_Weapon* TwoHandSword;



public:
	void AttackEnable(bool bEnable);
	bool IsAttack() const;

public:
	virtual void LevelUP(ELevelUpType eType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void LoadTwohandSword(const FString& strSocket, const FString& strMeshPath);

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
