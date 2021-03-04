// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Meteor.h"
#include "../NormalActor/Actor_Decal.h"
#include "../Character/Guardian/Guardian_Mage.h"

ASpell_Meteor::ASpell_Meteor()
{
	Mesh->SetEnableGravity(false);

	GetClassAsset(ASpell_MeteorExplosion, EffectAsset1, "Blueprint'/Game/05Spell/MeteorExplosion_BP.MeteorExplosion_BP_C'");

	if (EffectAsset1.Succeeded())
		MeteorExplosion = EffectAsset1.Class;
}

void ASpell_Meteor::SetMage(AGuardian_Mage * pMage)
{
}

void ASpell_Meteor::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_Meteor::CollisionBeginOverlap);

	AGuardian_Mage* pArcher = Cast<AGuardian_Mage>(GetOwner());

	SetSpellDmgRate(1.2);

	fLifeTime = 0.f;
	fLifeTimeMax = 1.f;
}

void ASpell_Meteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vPos = GetActorLocation();

	FVector vForward = GetActorForwardVector();

	vPos = vPos + (vForward * 1000 * DeltaTime);

	SetActorLocation(vPos);

	AGuardian_Mage* pMage = Cast<AGuardian_Mage>(GetOwner());

	AActor_Decal* pDecal = pMage->GetDecal();

	float fDist = FVector::Dist(vPos, pDecal->GetActorLocation());

	if (fDist <= 10.f)
	{
		m_bHide = true;
		SetHidden(true);
		CreateEffect();
	}

	if (m_bHide)
	{
		fLifeTime += DeltaTime;

		if (fLifeTime >= fLifeTimeMax)
		{
			Destroy();
		}
	}
}

void ASpell_Meteor::CreateEffect()
{
	FVector vPos = GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//AEffect_MagicMissile* pEffect = GetWorld()->SpawnActor<AEffect_MagicMissile>(Effect_Yellow, vPos, GetActorRotation(),
	//	tParams);
}

void ASpell_Meteor::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	FDamageEvent DmgEvent;

	AGuardian_Mage* pArcher = Cast<AGuardian_Mage>(GetOwner());

	if (IsValid(pArcher))
	{
		float fHp = OtherActor->TakeDamage(pArcher->GetState().iDamage*GetSpellDmgRate(), DmgEvent, pArcher->GetController(), this);


		if (fHp <= 0.f)
		{
			pArcher->EraseTarget();
		}
	}
}
