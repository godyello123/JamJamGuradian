// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_MagicMissile.h"

ASpell_MagicMissile::ASpell_MagicMissile()
{
	SetDamage(20.f);

	Mesh->SetEnableGravity(false);
}


void ASpell_MagicMissile::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetEnableGravity(false);
}

void ASpell_MagicMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector vPos = GetActorLocation();

	FVector vForward = GetActorForwardVector();

	vPos = vPos + (vForward * 1000*DeltaTime);

	SetActorLocation(vPos);
}

void ASpell_MagicMissile::CreateEffect()
{
	//매직미사일 이펙트 처리

}
