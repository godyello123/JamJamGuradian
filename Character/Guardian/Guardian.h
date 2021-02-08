// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../00Base/MasterActor.h"
#include "../../Projectile/Projectile.h"
#include "GameFramework/Character.h"
#include "Guardian.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FGuardianState
{
	GENERATED_USTRUCT_BODY()

public:
	FGuardianState()	:
		Damage(0),iHP(0),iHPMax(0),iMP(0),
		iMPMax(0),AttackSpeed(0.f)
	{

	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 iHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 iHPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float iMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 iMPMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float AttackSpeed;
};

UCLASS()
class MPSG_API AGuardian : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGuardian();

protected:
	int32 GuardianLevel;
	int32 CriticalChance;
	float CriticalRatio;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		AActor* Target;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bTarget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bCritical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FGuardianState		State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fAttackDist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		bool bAttack;

public:
	AActor* GetTarget() const;

protected:
	float MPFillTime;
	float MPFillTimeMax;
	float FillMP;

protected:
	class ASummoner* Summoner;

public:
	void SetFillMP(float iFill);

public:
	void SetState(int32 iDmg, int32 HP, int32 MP, float Speed);
	FGuardianState GetState() const;

public:
	void SetCriticalChance(int32 iChance);
	void SetCriticalRatio(float fRatio);
	int32 GetCriticalChance() const;
	float GetCriticalRatio() const;

public:
	void AddCriticalChance();
	void AddCriticalRatio();

public:
	void SetSummoner(class ASummoner* Sum);
	bool IsSummoner();

public:
	void AttackEnable(bool bEnable);
	bool IsAttack() const;

protected:
	void FillUpMP(float iValue,float fTime);


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

public:
	virtual void Motion();
	virtual void Attack();
	virtual void Skill();
	virtual void SearchTarget();

public:
	virtual void ShowUI(bool bShow);

 
};
