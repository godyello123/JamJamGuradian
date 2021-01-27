// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Monster.h"
#include "Monster_Beholder.generated.h"

/**
 * 
 */

UCLASS()
class MPSG_API AMonster_Beholder : public AMonster
{
	GENERATED_BODY()

public:
	AMonster_Beholder();

private:
	class UAnim_Beholder* Animation;
	float fDistance;
	float fMPRecovery;
	bool bAttack;

	//Test
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	AActor* P0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	AActor* P1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	AActor* P2;

	float fTime;
	//Test

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
