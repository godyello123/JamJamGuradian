// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../00Base/MasterActor.h"
#include "../../Projectile/Projectile.h"
#include "../../Effect/Effect_LevelUp.h"
#include "GameFramework/Character.h"
#include "Guardian.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EGUARDIAN_AI : uint8
{
	Idle,
	Attack,
	Groggy,
	Victory
};



USTRUCT(Atomic, BlueprintType)
struct FGuardianState
{
	GENERATED_USTRUCT_BODY()

public:
	FGuardianState()	:
		iDamage(0), 
		fTierGage_1(0),fTierGage_2(0),fTierGage_3(0),
		fTierGageMax_1(0),fTierGageMax_2(0),fTierGageMax_3(0),
		fAttackSpeed(0.f)
	{

	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 iDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fTierGage_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fTierGage_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fTierGage_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fTierGageMax_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fTierGageMax_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fTierGageMax_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		float fAttackSpeed;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 m_iDmgLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EElementalType m_eElementalType;
	UPROPERTY(Category = UI, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* UIComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		EGUARDIANLEVEL m_eLevel;


	class UGuardianUI* SpawnUI;
	UPROPERTY(Category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEffect_LevelUp> LightningLevelUp_EffectAsset;
	UPROPERTY(Category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEffect_LevelUp> FireLevelUp_EffectAsset;
	UPROPERTY(Category = Particle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEffect_LevelUp> IceLevelUp_EffectAsset;

protected:
	bool m_bDead;
	float m_fDeadTime;


public:
	EGUARDIANLEVEL GetGuardianLevel() const;
	void SetGuardianLevel(EGUARDIANLEVEL eLevel);

public:
	void SetElementalType(EElementalType eType);
	EElementalType GetElementalType() const;
	void RandElementalType();

public:
	AActor* GetTarget() const;

protected:
	float m_fFillTierGage_1;
	float m_fFillTierGage_2;
	float m_fFillTierGage_3;

public:
	void SetFillTierGage_1(float fTime);
	void SetFillTierGage_2(float fTime);
	void SetFillTierGage_3(float fTime);

protected:
	float m_fTierGageCurTime_1;
	float m_fTierGageCurTime_2;
	float m_fTierGageCurTime_3;
	float m_fTierGageTimeMax;

protected:
	class ASummoner* Summoner;

public:
	void SetState(int32 iDmg, float fTier1, float fTier2, float Tier3, float fSpeed);
	FGuardianState GetState() const;

public:
	void SetCriticalChance(int32 iChance);
	void SetCriticalRatio(float fRatio);
	int32 GetCriticalChance() const;
	float GetCriticalRatio() const;

public:
	void SetMeshMaterial(EElementalType eType);
	void SetMeshMaterialColor(FVector4& vColor);

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
	void FillUpTierGage_1(float iValue, float fTime);
	void FillUpTierGage_2(float iValue, float fTime);
	void FillUpTierGage_3(float iValue, float fTime);

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
	virtual void LevelUp(EGUARDIANLEVEL eLevel,EElementalType eType);

public:
	virtual void Dead();
	virtual void Motion();
	virtual void Attack();
	virtual void Skill();
	virtual void SearchTarget();

public:
	void ShowUI();
	void CreateEffectLevelUp(EElementalType eType);


	



 
};
