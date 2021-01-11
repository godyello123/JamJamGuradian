// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_MagicMissile.h"

ASpell_MagicMissile::ASpell_MagicMissile()
{
	SetDamage(20.f);

	Mesh->SetEnableGravity(false);


	GetClassAsset(AEffect_MagicMissile, EffectAsset, "Blueprint'/Game/06Effect/Effect_MM.Effect_MM_C'");

	if (EffectAsset.Succeeded())
		Effect = EffectAsset.Class;

	fLifeTime = 0;
	fLifeTimeMax = 3.f;
}


void ASpell_MagicMissile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);

	Collision->OnComponentBeginOverlap.AddDynamic(this, &ASpell_MagicMissile::CollisionBeginOverlap);

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

void ASpell_MagicMissile::CreateEffect()
{
	//매직미사일 이펙트 처리
	FVector vPos = GetActorLocation();

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AEffect_MagicMissile* pEffect = GetWorld()->SpawnActor<AEffect_MagicMissile>(Effect, vPos, GetActorRotation(),
		tParams);

}

void ASpell_MagicMissile::CollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//몬스터 데미지 주기
	CreateEffect();
	Destroy();
}
