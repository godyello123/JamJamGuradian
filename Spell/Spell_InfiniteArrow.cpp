// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_InfiniteArrow.h"


ASpell_InfiniteArrow::ASpell_InfiniteArrow()
{
	fLifeTime = 0;
	fLifeTimeMax = 1.5f;
}

void ASpell_InfiniteArrow::SetMage(AGuardian_Mage * pMage)
{
}

void ASpell_InfiniteArrow::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	/*Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_MagicMissile::CollisionBeginOverlap);*/
}

void ASpell_InfiniteArrow::Tick(float DeltaTime)
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

void ASpell_InfiniteArrow::CreateEffect()
{
}

void ASpell_InfiniteArrow::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//몬스터 데미지 주기
//	FDamageEvent DmgEvent;
//
//	AGuardian_Ranger* pOwner = Cast<AGuardian_Ranger>(GetOwner());
//
//	float fDmg = pOwner->GetState().iDamage * 2.5;
//
//	if (pOwner)
//	{
//		float fHP = OtherActor->TakeDamage(fDmg, DmgEvent, pOwner->GetController(), this);
//		CreateEffect();
//		if (fHP <= 0.f)
//		{
//			/*pOwner->EraseTarget();
//*/
//		}
//	}
//	Destroy();
}
