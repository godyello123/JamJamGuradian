// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile_SpawnGuardian.h"
#include "../UI/SpawnGuardianTileUI.h"
#include "Components/WidgetComponent.h"



// Sets default values
ATile_SpawnGuardian::ATile_SpawnGuardian()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	bClicked = false;
	Elemental = EElementalType::ET_Normal;

	UStaticMesh* Asset = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	if (IsValid(Asset))
	{
		Mesh->SetStaticMesh(Asset);
	}

	SetRootComponent(Mesh);

	UIComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));

	UIComponent->SetupAttachment(Mesh);

	UIComponent->SetWidgetSpace(EWidgetSpace::Screen);
	UIComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	UIComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));


	GetClassAsset(UUserWidget, WidgetClass, "WidgetBlueprint'/Game/10UI/SpawnTile_UI.SpawnTile_UI_C'");

	if (WidgetClass.Succeeded())
		UIComponent->SetWidgetClass(WidgetClass.Class);

	Tags.Add("Tile");

}

void ATile_SpawnGuardian::Click(bool _Click)
{
	bClicked = _Click;
}

bool ATile_SpawnGuardian::IsClick() const
{
	return bClicked;
}

void ATile_SpawnGuardian::SetElementalType(EElementalType eType)
{
	Elemental = eType;
}

EElementalType ATile_SpawnGuardian::GetElementalType() const
{
	return Elemental;
}

void ATile_SpawnGuardian::SpawnGuardian(EGuardianType eType)
{
	FVector vLoc = GetActorLocation();
	FRotator vRot = GetActorRotation();

	SetElementalType(EElementalType::ET_Normal);
}

// Called when the game starts or when spawned
void ATile_SpawnGuardian::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnUI = Cast< USpawnGuardianTileUI>(UIComponent->GetUserWidgetObject());
	SpawnUI->SetOwner(this);
	//SpawnUI->AddToViewport();
	SpawnUI->SetVisibility(ESlateVisibility::Collapsed);

}

// Called every frame
void ATile_SpawnGuardian::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile_SpawnGuardian::ShowUI(bool bShow)
{

}

void ATile_SpawnGuardian::ShowWidget()
{
	switch (SpawnUI->GetVisibility())
	{
	case ESlateVisibility::Visible:
		SpawnUI->SetVisibility(ESlateVisibility::Collapsed);
		break;
	case ESlateVisibility::Collapsed:
		SpawnUI->SetVisibility(ESlateVisibility::Visible);
	}
}

