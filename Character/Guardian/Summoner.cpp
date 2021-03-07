// Fill out your copyright notice in the Description page of Project Settings.


#include "Summoner.h"
#include "FreeCam.h"
#include "../../Animation/Monster/Anim_Summoner.h"
#include "../../Tile/TileManager.h"
#include "../../GameMode/DefenseGameInstance.h"
#include "../../UI/MainUI.h"
#include "../../GameMode/DefenseGameMode.h"

// Sets default values
ASummoner::ASummoner()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	/*GetObjectAsset(USkeletalMesh, MeshAsset, "SkeletalMesh'/Game/ModularRPGHeroesPBR/Meshes/OneMeshCharacters/PrinceSK.PrinceSK'");

	if (MeshAsset.Succeeded())
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);

	GetClassAsset(UAnim_Summoner, AnimAsset, "AnimBlueprint'/Game/00Summoner/Summoner_Anim.Summoner_Anim_C'");

	if (AnimAsset.Succeeded())
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);*/

	FreeCam = nullptr;
	TileManager = nullptr;
	YawOffset = 0.f;

}

ATileManager* ASummoner::GetTileManager() const
{
	return TileManager;
}

void ASummoner::CreateCamera(FVector& vLoc, FRotator& vRot)
{
	FreeCam = GetWorld()->SpawnActor<AFreeCam>(vLoc, vRot);

	FreeCam->SetSummoner(this);
}

void ASummoner::SetOffsetYaw(float Rot)
{
	YawOffset = Rot;
}

UAnim_Summoner* ASummoner::GetAnimation() const
{
	if (!(IsValid(Animation)))
	{
		PrintViewport(-1.f, FColor::Red, TEXT("Summoner Anim ERROR"));
		return nullptr;
	}
	else 
		return Animation;
}

// Called when the game starts or when spawned
void ASummoner::BeginPlay()
{
	Super::BeginPlay();

	FVector v = FVector(-150.f, 500.f, 1300.f);

	FRotator r2 = FRotator(FreeCamRotationOffsecPitch, FreeCamRotationOffsetYaw, FreeCamRotationOffsetRoll);

	CreateCamera(v, r2);

	//TileManager = GetWorld()->SpawnActor<ATileManager>();

	this->SetActorEnableCollision(false);

	SetHidden(true);
}

// Called every frame
void ASummoner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASummoner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("CamMoveHorizon"), this,
		&ASummoner::MoveHorizontal);
	PlayerInputComponent->BindAxis(TEXT("CamMoveVertical"), this,
		&ASummoner::MoveVertical);

}

void ASummoner::MoveHorizontal(float fScale)
{

	FreeCam->MoveHorizontal(fScale);
	
	//AddMovementInput(GetActorRightVector(), fScale);
}

void ASummoner::MoveVertical(float fScale)
{
	FreeCam->MoveVertical(fScale);
	//AddMovementInput(GetActorForwardVector(), fScale);
}

void ASummoner::ChangeAnim(ESummonerAnimType eType)
{
	if (Animation)
		Animation->ChangeAnim(eType);
}

