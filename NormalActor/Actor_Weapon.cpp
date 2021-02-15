// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Weapon.h"

// Sets default values
AActor_Weapon::AActor_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));


	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetRootComponent(Mesh);

}

// Called when the game starts or when spawned
void AActor_Weapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AActor_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActor_Weapon::LoadMesh(const FString& strPath)
{
	UStaticMesh* Asset = LoadObject<UStaticMesh>(nullptr, *strPath);

	if (IsValid(Asset))
	{
		Mesh->SetStaticMesh(Asset);
	}

}

void AActor_Weapon::SetScale(FVector & vScale)
{
	Mesh->SetRelativeScale3D(vScale);
}

