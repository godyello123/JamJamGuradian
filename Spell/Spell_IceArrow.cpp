// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_IceArrow.h"
#include "../Character/Guardian/Guardian_Archer.h"
#include "../Character/Monster/Monster.h"

ASpell_IceArrow::ASpell_IceArrow()
{
	Mesh->SetEnableGravity(false);

	particle1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle1"));
	particle1->SetupAttachment(Mesh);

	particle2 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle2"));
	particle2->SetupAttachment(Mesh);

	GetClassAsset(AEffect_IceArrow, EffectAsset1, "Blueprint'/Game/06Effect/BP_IceArrowEffect.BP_IceArrowEffect_C'");

	if (EffectAsset1.Succeeded())
		Effect = EffectAsset1.Class;

	fLifeTime = 0;
	fLifeTimeMax = 3.f;
}

void ASpell_IceArrow::SetSlowTime(float fTime)
{
	m_fSlowTime = fTime;
}

void ASpell_IceArrow::SetSlowRate(float fRate)
{
	m_fSlowRate = fRate;
}

float ASpell_IceArrow::GetSlowTime() const
{
	return m_fSlowTime;
}

float ASpell_IceArrow::GetSlowRate() const
{
	return m_fSlowRate;
}

void ASpell_IceArrow::SetArcher(AGuardian_Archer * pArcher)
{
	Archer = pArcher;
}

void ASpell_IceArrow::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_IceArrow::CollisionBeginOverlap);

	SetSpellDmgRate(0.7f);

	SetSlowRate(0.5);
	SetSlowTime(1.f);
}

void ASpell_IceArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vPos = GetActorLocation();

	FVector vForward = GetActorForwardVector();

	vPos = vPos + (vForward * 1000 * DeltaTime);

	SetActorLocation(vPos);

	fLifeTime += DeltaTime;

	if (fLifeTime >= fLifeTimeMax)
	{
		//CreateEffect();
		this->Destroy();
	}
}

void ASpell_IceArrow::CreateEffect()
{
	FVector vPos = GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEffect_IceArrow* pEffect = GetWorld()->SpawnActor<AEffect_IceArrow>(Effect, vPos, GetActorRotation(),
		tParams);
}

void ASpell_IceArrow::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FDamageEvent DmgEvent;

	AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

	float fDmg = pArcher->GetState().iDamage*GetSpellDmgRate();

	if (IsValid(pArcher))
	{
		AMonster* pMon = Cast<AMonster>(OtherActor);

		pMon->SlowEvent(m_fSlowTime, m_fSlowRate);

		float fHp = OtherActor->TakeDamage(fDmg, DmgEvent, pArcher->GetController(), this);

		if (fHp <= 0.f)
		{
			pArcher->EraseTarget();
		}

		CreateEffect();
	}

	Destroy();
}
