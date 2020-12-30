// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/Character.h"
#include "Guardian.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FGuardianState
{
	GENERATED_USTRUCT_BODY()

public:
	FGuardianState()
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
		int32 iMP;
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
		bool bCritical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FGuardianState		State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float	fAttackDist;

	float DetectTime;
	float DetectTimeMax;

public:
	void SetState(int32 iDmg, int32 HP, int32 MP, float Speed);

public:
	void SetCriticalChance(int32 iChance);
	void SetCriticalRatio(float fRatio);
	int32 GetCriticalChance() const;
	float GetCriticalRatio() const;

public:
	void AddCriticalChance();
	void AddCriticalRatio();



protected:
	class ASummoner* Summoner;

public:
	void SetSummoner(class ASummoner* Sum);
	bool IsSummoner();


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
  

};
