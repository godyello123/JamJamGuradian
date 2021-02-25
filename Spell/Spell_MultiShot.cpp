// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_MultiShot.h"
#include "../Character/Guardian/Guardian_Archer.h"
#include "../Character/Monster/Monster.h"

ASpell_MultiShot::ASpell_MultiShot()
{
	Mesh->SetEnableGravity(false);

	GetClassAsset(AEffect_Multishot, EffectAsset1, "Blueprint'/Game/06Effect/ArrowEffect_Yellow.ArrowEffect_Yellow_C'");

	if (EffectAsset1.Succeeded())
		Effect_Yellow = EffectAsset1.Class;

	GetClassAsset(AEffect_Multishot, EffectAsset2, "Blueprint'/Game/06Effect/ArrowEffect_Blue.ArrowEffect_Blue_C'");

	if (EffectAsset2.Succeeded())
		Effect_Blue = EffectAsset2.Class;

	GetClassAsset(AEffect_Multishot, EffectAsset3, "Blueprint'/Game/06Effect/ArrowEffect_Red.ArrowEffect_Red_C'");

	if (EffectAsset3.Succeeded())
		Effect_Red = EffectAsset3.Class;

	fLifeTime = 0;
	fLifeTimeMax = 3.f;
}

void ASpell_MultiShot::SetArcher(AGuardian_Archer* pArcher)
{
	Archer = pArcher;
}

void ASpell_MultiShot::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_MultiShot::CollisionBeginOverlap);

	SetSpellDmgRate(1.f);
}

void ASpell_MultiShot::Tick(float DeltaTime)
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

void ASpell_MultiShot::CreateEffect(EElementalType eType)
{
	FVector vPos = GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	switch (eType)
	{
	case EElementalType::ET_Normal:
	{
		AEffect_Multishot* pEffect = GetWorld()->SpawnActor<AEffect_Multishot>(Effect_Yellow, vPos, GetActorRotation(),
			tParams);
	}
		break;
	case EElementalType::ET_Fire:
	{
		AEffect_Multishot* pEffect = GetWorld()->SpawnActor<AEffect_Multishot>(Effect_Red, vPos, GetActorRotation(),
			tParams);
	}
		break;
	case EElementalType::ET_Ice:
	{
		AEffect_Multishot* pEffect = GetWorld()->SpawnActor<AEffect_Multishot>(Effect_Blue, vPos, GetActorRotation(),
			tParams);
	}
		break;
	}
}

void ASpell_MultiShot::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FDamageEvent DmgEvent;

	AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

	float fDmg = pArcher->GetState().iDamage*GetSpellDmgRate();

	if (IsValid(pArcher))
	{	
		float fHp = OtherActor->TakeDamage(fDmg, DmgEvent, pArcher->GetController(), this);

		if (fHp <= 0.f)
		{
			pArcher->EraseTarget();
		}

		CreateEffect(pArcher->GetElementalType());
	}
	
	Destroy();

}

