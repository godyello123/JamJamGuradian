// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell_Static.h"
#include "Spell_StaticArrow.h"

ASpell_Static::ASpell_Static()
{

}

void ASpell_Static::SetTargetCount(int32 iCount)
{
	m_iTargetCount = iCount;
}

int32 ASpell_Static::GetTargetCount() const
{
	return m_iTargetCount;
}

void ASpell_Static::BeginPlay()
{
	Super::BeginPlay();
}

void ASpell_Static::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
