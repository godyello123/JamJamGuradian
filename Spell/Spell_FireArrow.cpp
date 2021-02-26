// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_FireArrow.h"

ASpell_FireArrow::ASpell_FireArrow()
{

}

void ASpell_FireArrow::BeginPlay()
{
	Super::BeginPlay();
}

void ASpell_FireArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpell_FireArrow::CreateEffect()
{

}

void ASpell_FireArrow::CollisionBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}
