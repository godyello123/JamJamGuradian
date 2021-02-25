// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile_SpawnGuardian.h"
#include "Components/WidgetComponent.h"
#include "../Character/Guardian/Guardian_Archer.h"
#include "../Character/Guardian/Guardian_Knight.h"
#include "../Character/Guardian/Guardian_Mage.h"




// Sets default values
ATile_SpawnGuardian::ATile_SpawnGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Elemental = EElementalType::ET_Normal;

	UStaticMesh* Asset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	//Mesh->SetMaterial()
	if (IsValid(Asset))
	{
		Mesh->SetStaticMesh(Asset);
	}

	SetRootComponent(Mesh);

	UMaterialInstance* mtrl = 
		LoadObject<UMaterialInstance>
		(nullptr, TEXT("MaterialInstanceConstant'/Game/07Material/Mtrl_Tile2.Mtrl_Tile2'"));
	
	Mesh->SetMaterial(0, mtrl);

	bShowTile = false;

	Tags.Add("Tile");

	this->SetActorScale3D(FVector(1.5f, 1.5f, 1.f));
}

bool ATile_SpawnGuardian::IsShow()
{
	return bShowTile;
}

void ATile_SpawnGuardian::SetElementalType(EElementalType eType)
{
	Elemental = eType;
}

EElementalType ATile_SpawnGuardian::GetElementalType() const
{
	return Elemental;
}

void ATile_SpawnGuardian::SpawnGuardian(int32 iType)
{
	if (iType == 0)
	{
		FVector vLoc = GetActorLocation();
		vLoc.Z += 100.f;
		FRotator vRot = GetActorRotation();
		AGuardian_Archer* pGuardian = GetWorld()->SpawnActor<AGuardian_Archer>(vLoc, vRot);
		pGuardian->RandElementalType();
	}
	else if (iType == 1)
	{
		FVector vLoc = GetActorLocation();
		vLoc.Z += 100.f;
		FRotator vRot = GetActorRotation();
		AGuardian_Mage* pGuardian = GetWorld()->SpawnActor<AGuardian_Mage>(vLoc, vRot);
		pGuardian->RandElementalType();
	}
	else if (iType == 2)
	{
		FVector vLoc = GetActorLocation();
		vLoc.Z += 100.f;
		FRotator vRot = GetActorRotation();
		AGuardian_Knight* pGuardian = GetWorld()->SpawnActor<AGuardian_Knight>(vLoc, vRot);
		pGuardian->RandElementalType();
	}
	else
		return;
}

// Called when the game starts or when spawned
void ATile_SpawnGuardian::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile_SpawnGuardian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile_SpawnGuardian::EnableTile(bool bEnable)
{
	bShowTile = bEnable;

	Mesh->SetVisibility(bShowTile);
	
	if (!bShowTile)
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	else
	{
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		int32 iRand = FMath::RandRange(0, 2);
		SpawnGuardian(iRand);
	}

}

