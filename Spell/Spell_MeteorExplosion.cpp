// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_MeteorExplosion.h"

ASpell_MeteorExplosion::ASpell_MeteorExplosion()
{

}

void ASpell_MeteorExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void ASpell_MeteorExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpell_MeteorExplosion::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}
