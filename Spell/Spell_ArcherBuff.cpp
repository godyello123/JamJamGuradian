// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_ArcherBuff.h"
#include "../Character/Guardian/Guardian_Archer.h"

ASpell_ArcherBuff::ASpell_ArcherBuff()
{
	fLifeTime = 0.f;
	fLifeTimeMax = 10.f;
}

void ASpell_ArcherBuff::SetArcher(AGuardian_Archer * pArcher)
{
	Archer = pArcher;
}

void ASpell_ArcherBuff::BeginPlay()
{
	Super::BeginPlay();

	Collision->SetEnableGravity(false);
	Mesh->SetEnableGravity(false);
	Mesh->SetVisibility(false);
}

void ASpell_ArcherBuff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	fLifeTime += DeltaTime;

	if (fLifeTime >= fLifeTimeMax)
	{
		AGuardian_Archer* pArcher = Cast<AGuardian_Archer>(GetOwner());
		Destroy();
	}
}
