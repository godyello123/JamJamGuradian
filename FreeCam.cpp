// Fill out your copyright notice in the Description page of Project Settings.


#include "FreeCam.h"
#include "Summoner.h"
#include "SummonerController.h"
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
	

	bChasePlayer = true;
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
		PrintViewport(-1, FColor::Red, TEXT("FreeCam : On"));
	}
}

// Called every frame
void AFreeCam::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bChasePlayer)
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			break;
		case EFreeCamDir::Up:
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
		AAIController* pAI = GetController<AAIController>();

		if(IsValid(pAI))
			pAI->MoveToLocation(Summoner->GetActorLocation());
	}
}

// Called to bind functionality to input
void AFreeCam::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFreeCam::MoveHorizontal(float fScale)
{
	if (fScale > 0.f)
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			CamDir = EFreeCamDir::Right;
			break;
		case EFreeCamDir::Up:
			CamDir = EFreeCamDir::UpRight;
			break;
		case EFreeCamDir::Down:
			CamDir = EFreeCamDir::DownRight;
			break;
		case EFreeCamDir::Right:
			CamDir = EFreeCamDir::Right;
			break;
		case EFreeCamDir::Left:
			CamDir = EFreeCamDir::Right;
			break;
		case EFreeCamDir::UpRight:
			CamDir = EFreeCamDir::UpRight;
			break;
		case EFreeCamDir::UpLeft:
			CamDir = EFreeCamDir::UpRight;
			break;
		case EFreeCamDir::DownRight:
			CamDir = EFreeCamDir::DownRight;
			break;
		case EFreeCamDir::DownLeft:
			CamDir = EFreeCamDir::DownRight;
			break;
		}

	
	}
	else if (fScale < 0.f)
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			CamDir = EFreeCamDir::Left;
			break;
		case EFreeCamDir::Up:
			CamDir = EFreeCamDir::UpLeft;
			break;
		case EFreeCamDir::Down:
			CamDir = EFreeCamDir::DownLeft;
			break;
		case EFreeCamDir::Right:
			CamDir = EFreeCamDir::Left;
			break;
		case EFreeCamDir::Left:
			CamDir = EFreeCamDir::Left;
			break;
		case EFreeCamDir::UpRight:
			CamDir = EFreeCamDir::UpLeft;
			break;
		case EFreeCamDir::UpLeft:
			CamDir = EFreeCamDir::UpLeft;
			break;
		case EFreeCamDir::DownRight:
			CamDir = EFreeCamDir::DownLeft;
			break;
		case EFreeCamDir::DownLeft:
			CamDir = EFreeCamDir::DownLeft;
			break;
		}

		
	}
	else
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			CamDir = EFreeCamDir::None;
			break;
		case EFreeCamDir::Up:
			CamDir = EFreeCamDir::Up;
			break;
		case EFreeCamDir::Down:
			CamDir = EFreeCamDir::Down;
			break;
		case EFreeCamDir::Right:
			CamDir = EFreeCamDir::None;
			break;
		case EFreeCamDir::Left:
			CamDir = EFreeCamDir::None;
			break;
		case EFreeCamDir::UpRight:
			CamDir = EFreeCamDir::Up;
			break;
		case EFreeCamDir::UpLeft:
			CamDir = EFreeCamDir::Up;
			break;
		case EFreeCamDir::DownRight:
			CamDir = EFreeCamDir::Down;
			break;
		case EFreeCamDir::DownLeft:
			CamDir = EFreeCamDir::Down;
			break;
		}
	}

	if (CamDir == EFreeCamDir::None)
	{
		bChasePlayer = true;
	}
	else
	{
		bChasePlayer = false;
	}
}

void AFreeCam::MoveVertical(float fScale)
{
	if (fScale > 0.f)
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			CamDir = EFreeCamDir::Up;
			break;
		case EFreeCamDir::Up:
			CamDir = EFreeCamDir::Up;
			break;
		case EFreeCamDir::Down:
			CamDir = EFreeCamDir::Up;
			break;
		case EFreeCamDir::Right:
			CamDir = EFreeCamDir::UpRight;
			break;
		case EFreeCamDir::Left:
			CamDir = EFreeCamDir::UpLeft;
			break;
		case EFreeCamDir::UpRight:
			CamDir = EFreeCamDir::UpRight;
			break;
		case EFreeCamDir::UpLeft:
			CamDir = EFreeCamDir::UpRight;
			break;
		case EFreeCamDir::DownRight:
			CamDir = EFreeCamDir::DownRight;
			break;
		case EFreeCamDir::DownLeft:
			CamDir = EFreeCamDir::DownRight;
			break;
		}
	}
	else if (fScale < 0.f)
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			CamDir = EFreeCamDir::Down;
			break;
		case EFreeCamDir::Up:
			CamDir = EFreeCamDir::Down;
			break;
		case EFreeCamDir::Down:
			CamDir = EFreeCamDir::Down;
			break;
		case EFreeCamDir::Right:
			CamDir = EFreeCamDir::DownRight;
			break;
		case EFreeCamDir::Left:
			CamDir = EFreeCamDir::DownLeft;
			break;
		case EFreeCamDir::UpRight:
			CamDir = EFreeCamDir::DownRight;
			break;
		case EFreeCamDir::UpLeft:
			CamDir = EFreeCamDir::DownLeft;
			break;
		case EFreeCamDir::DownRight:
			CamDir = EFreeCamDir::DownRight;
			break;
		case EFreeCamDir::DownLeft:
			CamDir = EFreeCamDir::DownLeft;
			break;
		}
	}
	else
	{
		switch (CamDir)
		{
		case EFreeCamDir::None:
			CamDir = EFreeCamDir::None;
			break;
		case EFreeCamDir::Up:
			CamDir = EFreeCamDir::None;
			break;
		case EFreeCamDir::Down:
			CamDir = EFreeCamDir::None;
			break;
		case EFreeCamDir::Right:
			CamDir = EFreeCamDir::Right;
			break;
		case EFreeCamDir::Left:
			CamDir = EFreeCamDir::Left;
			break;
		case EFreeCamDir::UpRight:
			CamDir = EFreeCamDir::Right;
			break;
		case EFreeCamDir::UpLeft:
			CamDir = EFreeCamDir::Left;
			break;
		case EFreeCamDir::DownRight:
			CamDir = EFreeCamDir::Right;
			break;
		case EFreeCamDir::DownLeft:
			CamDir = EFreeCamDir::Left;
			break;
		}
	}

	if (CamDir == EFreeCamDir::None)
	{
		bChasePlayer = true;
	}
	else
	{
		bChasePlayer = false;
	}
}

