// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_ExplosionArrow.h"
#include "../Character/Guardian/Guardian_Archer.h"

ASpell_ExplosionArrow::ASpell_ExplosionArrow()
{

	Mesh->SetEnableGravity(false);

	GetClassAsset(ASpell_Explosion, EffectAsset1, "Blueprint'/Game/05Spell/Explosion_BP.Explosion_BP_C'");

	if (EffectAsset1.Succeeded())
		ExplosionAsset = EffectAsset1.Class;


	m_fLifeTime = 0;
	m_fLifeTimeMax = 7.f;
}

AGuardian_Archer * ASpell_ExplosionArrow::GetArcher() const
{
	return m_pArcher;
}

void ASpell_ExplosionArrow::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_ExplosionArrow::CollisionBeginOverlap);

	AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

	m_pArcher = pArcher;

	SetSpellDmgRate(1.2);
}

void ASpell_ExplosionArrow::Tick(float DeltaTime)
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

void ASpell_ExplosionArrow::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FDamageEvent DmgEvent;

	AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

	if (IsValid(pArcher))
	{
		float fHp = OtherActor->TakeDamage(pArcher->GetState().iDamage*GetSpellDmgRate(), DmgEvent, m_pArcher->GetController(), this);

		m_vPos = OtherActor->GetActorLocation();

		if (fHp <= 0.f)
		{
			pArcher->EraseTarget();
		}

		CreateExplosion();

		//Destroy();
	}
	Destroy();

}

void ASpell_ExplosionArrow::CreateExplosion()
{
	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = this;

	ASpell_Explosion* pEffect = GetWorld()->SpawnActor<ASpell_Explosion>(ExplosionAsset, m_vPos, GetActorRotation(),
		tParams);
}
