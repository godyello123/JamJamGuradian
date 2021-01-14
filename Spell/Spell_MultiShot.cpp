// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_MultiShot.h"
#include "../Character/Guardian/Guardian_Archer.h"

ASpell_MultiShot::ASpell_MultiShot()
{
	SetDamage(20.f);

	Mesh->SetEnableGravity(false);

	GetClassAsset(AEffect_Multishot, EffectAsset, "Blueprint'/Game/06Effect/Effect_Ms.Effect_Ms_C'");

	if (EffectAsset.Succeeded())
		Effect = EffectAsset.Class;

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

}

void ASpell_MultiShot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vPos = GetActorLocation();

	FVector vForward = GetActorForwardVector();

	vPos = vPos + (vForward * 100 * DeltaTime);

	SetActorLocation(vPos);

	//fLifeTime += DeltaTime;

	//if (fLifeTime >= fLifeTimeMax)
	//{
	//	//CreateEffect();
	//	this->Destroy();
	//}
}

void ASpell_MultiShot::CreateEffect()
{
	FVector vPos = GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEffect_Multishot* pEffect = GetWorld()->SpawnActor<AEffect_Multishot>(Effect, vPos, GetActorRotation(),
		tParams);
}

void ASpell_MultiShot::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FDamageEvent DmgEvent;

	AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());

	if (IsValid(pArcher))
	{
		pArcher->Test();
		OtherActor->TakeDamage(GetDamage(), DmgEvent, pArcher->GetController(), this);
		CreateEffect();
	}
	
	Destroy();

}
