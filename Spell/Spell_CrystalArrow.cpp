// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_CrystalArrow.h"
#include "../Character/Guardian/Guardian_Archer.h"
#include "../Character/Monster/Monster.h"

ASpell_CrystalArrow::ASpell_CrystalArrow()
{
	particle1 = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle1"));
	particle1->SetupAttachment(Mesh);

	Mesh->SetEnableGravity(false);

	GetClassAsset(AEffect_Crystal, EffectAsset1, "Blueprint'/Game/06Effect/BP_CrystalArrow.BP_CrystalArrow_C'");

	if (EffectAsset1.Succeeded())
		EffectAsset = EffectAsset1.Class;


	m_fLifeTime = 0;
	m_fLifeTimeMax = 20.f;


}

void ASpell_CrystalArrow::SetSlowTime(float fTime)
{
}

void ASpell_CrystalArrow::SetSlowRate(float fRate)
{
}

float ASpell_CrystalArrow::GetSlowTime() const
{
	return 0.0f;
}

float ASpell_CrystalArrow::GetSlowRate() const
{
	return 0.0f;
}

void ASpell_CrystalArrow::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_CrystalArrow::CollisionBeginOverlap);

	AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

	SetSpellDmgRate(0.7f);

	SetSlowRate(0.8);
	SetSlowTime(1.f);
}

void ASpell_CrystalArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vPos = GetActorLocation();

	FVector vForward = GetActorForwardVector();

	vPos = vPos + (vForward * 1000 * DeltaTime);

	SetActorLocation(vPos);

	m_fLifeTime += DeltaTime;

	if (m_fLifeTime >= m_fLifeTimeMax)
	{
		//CreateEffect();
		this->Destroy();
	}
}

void ASpell_CrystalArrow::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
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

void ASpell_CrystalArrow::CreateEffect()
{
	FVector vPos = GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEffect_Crystal* pEffect = GetWorld()->SpawnActor<AEffect_Crystal>(EffectAsset, vPos, GetActorRotation(),
		tParams);
}
