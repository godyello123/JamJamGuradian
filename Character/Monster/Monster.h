// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../00Base/GameInfo.h"
#include "GameFramework/Character.h"
#include "../../NormalActor/Actor_Gem.h"
#include "../../NormalActor/Actor_Spline.h"
#include "Monster.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FMonsterState
{
	GENERATED_USTRUCT_BODY()

public:
	FMonsterState()	:
		Damage(0),iHP(0),iHPMax(0),iMP(0),
		iMPMax(0),AttackSpeed(0.f),MoveSpeed(0.f)
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float MoveSpeed;
};


UCLASS()
class MPSG_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	class ADemonGate* Gate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FMonsterState		State;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		TArray<AActor*> PathArray;
	UPROPERTY(Category = Gem, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor_Gem> FireGem;
	UPROPERTY(Category = Gem, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor_Gem> ICEGem;
	UPROPERTY(Category = Gem, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor_Gem> HolyGem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	AActor_Spline* m_pSpline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float SplineTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float m_fSlowRate;

protected:
	class UMaterialInstance* MaterialDynamicInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float m_fBurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float m_fFilter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float m_fTemperature;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float m_fBurnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float m_fGroggyTime;

	float m_fCurGroggyTime;
public:
	void SetGroggyTime(float fTime);
	void AddCurGroggyTime(float fTime);
	float GetCurGroggyTime() const;
	float GetGroggyTime() const;

public:
	void GroggyEnd();

public:
	void SetSlowRate(float fRate);

	

public:
	void AddSplineTime(float fTime);
	float GetSplineTime();
	void ClearSplineTime();
	
public:
	void SetSplice(AActor_Spline* pSpline);

public:
	AActor_Spline* GetSpline() const
	{
		if (m_pSpline)
		{
			return m_pSpline;
		}
		else
			return nullptr;
	}

protected:
	bool bDead;
	bool bGroggy;

public:
	bool IsDead();
	void Dead();

public:
	bool IsGroggy();
	
protected:
	int32 iPathPoint;

public:
	void SetDemonGate(class ADemonGate* pGate);
public:
	void AddPathPoint(AActor* pActor);

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

protected:
	void SetMonsterState(int32 iDamage, int32 iHP, int32 iMP, float fATSpeed, float fMoveSpeed);

public:
	FMonsterState GetMonsterState() const;

public:
	void CreateGem(int32 iGemCount);

public:
	void SetBurnEffectMaterial();
public:
	void SetBurn(float fBurn);
	void SetFilter(float fFilter);
	void SetTemperature(float fTemperature);

public:
	virtual void Skill();
	virtual void Groggy();
};
