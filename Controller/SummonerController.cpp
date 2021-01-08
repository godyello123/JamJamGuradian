// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../Character/Guardian/Summoner.h"

ASummonerController::ASummonerController()
{

}

void ASummonerController::BeginPlay()
{

}

void ASummonerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRButtonDown)
	{
		MoveSummoner(DeltaTime);
	}
}

void ASummonerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);


}

void ASummonerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("ClickR"), EInputEvent::IE_Pressed,
		this, &ASummonerController::RButtonClick);

	InputComponent->BindAction(TEXT("ClickR"), EInputEvent::IE_Released,
		this, &ASummonerController::RButtonRelease);

}

void ASummonerController::LButtonClick()
{
	bLButtonDown = true;
}

void ASummonerController::LButtonRelease()
{
	bLButtonDown = false;
}

void ASummonerController::RButtonClick()
{
	bRButtonDown = true;
}

void ASummonerController::RButtonRelease()
{
	bRButtonDown = false;
}

bool ASummonerController::IsLButton() const
{
	return bLButtonDown;
}

bool ASummonerController::IsRButton() const
{
	return bRButtonDown;
}

void ASummonerController::Picking(float DeltaTime)
{
	FHitResult result;

	bool bHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
		false, result);

}

void ASummonerController::MoveSummoner(float fDeltaTime)
{
	FHitResult result;

	bool bHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
		false, result);

	if (bHit)
	{
		ASummoner* Summoner = Cast<ASummoner>(GetPawn());

		if (IsValid(Summoner))
		{
			FVector v = result.ImpactPoint;
			FVector v2 = Summoner->GetActorLocation();

			FVector v3 = v - v2;
			v3.Normalize();

			Summoner->SetActorRotation(FRotator(0.f, v3.Rotation().Yaw, 0.f));

			Summoner->ChangeAnim(ESummonerAnimType::SAT_Move);

			
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, result.ImpactPoint);
		}
	}
}


