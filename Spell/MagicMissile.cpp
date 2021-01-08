// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicMissile.h"

// Sets default values
AMagicMissile::AMagicMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	iDamage = 0;
}

void AMagicMissile::SetDamage(int32 iDmg)
{
	iDamage = iDmg;
}

int32 AMagicMissile::GetDamage() const
{
	return iDamage;
}

// Called when the game starts or when spawned
void AMagicMissile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagicMissile::CreateEffect()
{
	//몬스터 닿으면 터질 이펙트
}

