// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_MagicMissile.h"
#include "../Character/Guardian/Guardian_Mage.h"

ASpell_MagicMissile::ASpell_MagicMissile()
{
	Mesh->SetEnableGravity(false);


	GetClassAsset(AEffect_MagicMissile, EffectAsset, "Blueprint'/Game/06Effect/BoltEffect_Yellow.BoltEffect_Yellow_C'");

	if (EffectAsset.Succeeded())
		Effect_Yellow = EffectAsset.Class;

	GetClassAsset(AEffect_MagicMissile, EffectAsset1, "Blueprint'/Game/06Effect/BoltEffect_REd.BoltEffect_REd_C'");

	if (EffectAsset1.Succeeded())
		Effect_Red = EffectAsset1.Class;

	GetClassAsset(AEffect_MagicMissile, EffectAsset2, "Blueprint'/Game/06Effect/BoltEffect_Blue.BoltEffect_Blue_C'");

	if (EffectAsset2.Succeeded())
		Effect_Blue = EffectAsset2.Class;

	fLifeTime = 0;
	fLifeTimeMax = 1.5f;
}


void ASpell_MagicMissile::SetMage(AGuardian_Mage* pMage)
{
	//Mage = pMage;
}

void ASpell_MagicMissile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_MagicMissile::CollisionBeginOverlap);

	SetSpellDmgRate(2.f);

}

void ASpell_MagicMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vPos = GetActorLocation();

	FVector vForward = GetActorForwardVector();

	vPos = vPos + (vForward * 1000*DeltaTime);

	SetActorLocation(vPos);

	fLifeTime += DeltaTime;

	if (fLifeTime >= fLifeTimeMax)
	{
		//CreateEffect();
		this->Destroy();
	}
}

void ASpell_MagicMissile::CreateEffect(EElementalType eType)
{
	FVector vPos = GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	switch (eType)
	{
	case EElementalType::ET_Normal:
	{
		AEffect_MagicMissile* pEffect = GetWorld()->SpawnActor<AEffect_MagicMissile>(Effect_Yellow, vPos, GetActorRotation(),
			tParams);
	}
		break;
	case EElementalType::ET_Fire:
	{
		AEffect_MagicMissile* pEffect = GetWorld()->SpawnActor<AEffect_MagicMissile>(Effect_Red, vPos, GetActorRotation(),
			tParams);
	}
		break;
	case EElementalType::ET_Ice:
	{
		AEffect_MagicMissile* pEffect = GetWorld()->SpawnActor<AEffect_MagicMissile>(Effect_Blue, vPos, GetActorRotation(),
			tParams);
	}
		break;
	}
}

void ASpell_MagicMissile::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	////몬스터 데미지 주기
	FDamageEvent DmgEvent;

	AGuardian_Mage* pOwner = Cast<AGuardian_Mage>(GetOwner());

	if (pOwner)
	{
		float fHP=OtherActor->TakeDamage(pOwner->GetState().iDamage*GetSpellDmgRate(), DmgEvent, pOwner->GetController(), this);
		
		if (fHP <= 0.f)
		{
			pOwner->EraseTarget();
		}

		CreateEffect(pOwner->GetElementalType());
	}
	Destroy();
}
