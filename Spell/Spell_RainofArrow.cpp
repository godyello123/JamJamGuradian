// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_RainofArrow.h"
#include "../NormalActor/Actor_Decal.h"
#include "../Character/Guardian/Guardian_Archer.h"

ASpell_RainofArrow::ASpell_RainofArrow()
{
	Mesh->SetEnableGravity(false);

	GetClassAsset(ASpell_ExplosionArrow, ArrowAsset, "Blueprint'/Game/05Spell/ExplosionArrow_BP.ExplosionArrow_BP_C'");

	if (ArrowAsset.Succeeded())
		Arrow = ArrowAsset.Class;
}

void ASpell_RainofArrow::BeginPlay()
{
	Super::BeginPlay();

	m_fLifeTime = 0.f;
	m_fLIfeTimeMax = 10.f;
	m_fSpawnArrowTime = 0.f;
	m_fSpawnArrowTimeMax = 0.5;
	m_bEnable = false;

	Mesh->SetEnableGravity(false);
}

void ASpell_RainofArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_fSpawnArrowTime += DeltaTime;

	if (m_bDestroy)
	{
		m_fLifeTime += DeltaTime;
		if (m_fLifeTime >= m_fLIfeTimeMax)
		{
			AGuardian_Archer* pOwner = Cast<AGuardian_Archer>(GetOwner());
			Destroy();
		}

	}

	if (m_fSpawnArrowTime >= m_fSpawnArrowTimeMax)
	{
		CreateArrow();
	}

}

void ASpell_RainofArrow::CreateArrow()
{
	if (m_iArrowCount >= 10)
	{
		m_bDestroy = true;
		return;
	}


	FRotator vRot = FRotator(-90.f, 0.f, 0.f);

	FActorSpawnParameters tParams;

	tParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	tParams.Owner = GetOwner();

	AGuardian_Archer* pOwner = Cast<AGuardian_Archer>(GetOwner());

	FVector vLoc = pOwner->GetDecal()->GetActorLocation();
	vLoc.Z = 1000.f;
	float fX = FMath::FRandRange(-50.f, 50.f);
	float fY = FMath::FRandRange(-50.f, 50.f);
	vLoc.Y += fY;
	vLoc.X += fX;
	ASpell_ExplosionArrow* pArrow = GetWorld()->SpawnActor<ASpell_ExplosionArrow>(Arrow, vLoc, vRot,
		tParams);

	pArrow->SetActorRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	m_fSpawnArrowTime = 0.f;

	++m_iArrowCount;
}
