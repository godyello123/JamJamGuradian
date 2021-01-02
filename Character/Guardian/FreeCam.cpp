// Fill out your copyright notice in the Description page of Project Settings.
#define CamSpeed 600.f

#include "FreeCam.h"
#include "Summoner.h"
#include "../../Controller/SummonerController.h"
#include "AIController.h"


// Sets default values
AFreeCam::AFreeCam()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	TICKON;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));

	Arm->SetupAttachment(GetMesh());
	Camera->SetupAttachment(Arm);
	

	bChasePlayer = false;
	CamDir = EFreeCamDir::None;

	Summoner = nullptr;
}

void AFreeCam::SetSummoner(ASummoner* Sum)
{
	Summoner = Sum;
}

// Called when the game starts or when spawned
void AFreeCam::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (OurPlayerController)
	{
		OurPlayerController->SetViewTarget(this);
		//PrintViewport(-1, FColor::Red, TEXT("FreeCam : On"));
	}

}

// Called every frame
void AFreeCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CamDir = EFreeCamDir::Up;
	FVector vLoc = GetActorLocation();

	if (!bChasePlayer)
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			SetActorLocation(vLoc);
			break;
		case EFreeCamDir::Up:
		{
			//vLoc.X =vLoc.X+ (100.f * DeltaTime);
			//SetActorLocation(vLoc);
		}
			break;
		case EFreeCamDir::Down:
			break;
		case EFreeCamDir::Right:
			break;
		case EFreeCamDir::Left:
			break;
		case EFreeCamDir::UpRight:
			break;
		case EFreeCamDir::UpLeft:
			break;
		case EFreeCamDir::DownRight:
			break;
		case EFreeCamDir::DownLeft:
			break;
		}
	}
	else
	{
		/*AAIController* pAI = GetController<AAIController>();

		if(IsValid(pAI))
			pAI->MoveToLocation(Summoner->GetActorLocation());*/
		
	}
}

// Called to bind functionality to input
void AFreeCam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFreeCam::MoveHorizontal(float fScale)
{
	FVector vLoc = GetActorLocation();
	float fTime = GetWorld()->GetDeltaSeconds();

	if (fScale < 0.f)
	{
		vLoc.Y =vLoc.Y+ fScale * fTime* CamSpeed;
		SetActorLocation(vLoc);
	}
	else if (fScale > 0.f)
	{
		vLoc.Y =vLoc.Y+ fScale * fTime * CamSpeed;
		SetActorLocation(vLoc);
	}
	
}

void AFreeCam::MoveVertical(float fScale)
{
	FVector vLoc = GetActorLocation();
	float fTime = GetWorld()->GetDeltaSeconds();

	if (fScale < 0.f)
	{
		vLoc.X = vLoc.X + fScale * fTime * CamSpeed;
		SetActorLocation(vLoc);
	}
	else if (fScale > 0.f)
	{
		vLoc.X = vLoc.X + fScale * fTime * CamSpeed;
		SetActorLocation(vLoc);
	}
}

