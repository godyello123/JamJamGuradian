// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Castle.h"

// Sets default values
AActor_Castle::AActor_Castle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	DMesh = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DMesh"));

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Mesh_Col"));

	SetRootComponent(Sphere);

	Sphere->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	Sphere->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

	//Mesh->SetupAttachment(Sphere);
	DMesh->SetupAttachment(Sphere);

	//GetObjectAsset(UDestructibleMesh, MeshAsset, "DestructibleMesh'/Game/05StaticMesh/Castle_A_DM.Castle_A_DM_C'");

	//if (MeshAsset.Succeeded())
	//{
	//	//DMesh->SetDestructibleMesh(MeshAsset.Object);
	//	//DMesh->SetStaticMesh(MeshAsset.Object);
	//	DMesh->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	//	DMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
	//}

	DMesh->SetWorldLocation(FVector(0.f, 0.f, 0.f));
	DMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));

	iCastleMaxHP = 20;
	iCastleHP = iCastleMaxHP;
}

// Called when the game starts or when spawned
void AActor_Castle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AActor_Castle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AActor_Castle::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	iCastleHP -=(int32)DamageAmount;
	PrintViewport(10.f, FColor::Red, TEXT("Castle_Damage"));
	if (iCastleHP <= 0)
	{
		//¼ººÎ¼ÅÁü!!!!!
		Destroy();
	}

	return 0.0f;
}

