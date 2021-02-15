// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../Character/Guardian/Summoner.h"
#include "../Character/Guardian/Guardian.h"
#include "../Character/Monster/Monster.h"
#include "../Tile/Tile_SpawnGuardian.h"

ASummonerController::ASummonerController()
{
	
}

void ASummonerController::BeginPlay()
{
	ClickedActor = nullptr;
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

	InputComponent->BindAction(TEXT("ClickL"), EInputEvent::IE_Pressed,
		this, &ASummonerController::LButtonClick);


	InputComponent->BindAction(TEXT("ClickL"), EInputEvent::IE_Pressed,
		this, &ASummonerController::LButtonRelease);

}

void ASummonerController::PastProcess()
{
	if (IsValid(ClickedActor))
	{
		if (ClickedActor->Tags.Num() > 0)
		{
			if (ClickedActor->Tags[0] == "Guardian")
			{
				//기존에 켜져있던 ui 안보이기
				AGuardian* pGuardian = Cast<AGuardian>(ClickedActor);
				pGuardian->ShowUI();
			}
			else if (ClickedActor->Tags[0] == "Monster")
			{

			}
			else if (ClickedActor->Tags[0] == "Tile")
			{

			}
		}
	}
}

void ASummonerController::CurrentProcess(AActor* _Actor)
{
	ClickedActor = _Actor;

	if (IsValid(ClickedActor))
	{
		if (ClickedActor->Tags.Num() > 0)
		{
			if (ClickedActor->Tags[0] == "Guardian")
			{
				AGuardian* pGuardian = Cast<AGuardian>(ClickedActor);
				pGuardian->ShowUI();
			}
			else if (ClickedActor->Tags[0] == "Monster")
			{

			}
			else if (ClickedActor->Tags[0] == "Tile")
			{
				//ATile_SpawnGuardian* pTile = Cast<ATile_SpawnGuardian>(ClickedActor);

				//if (!pTile->IsClick())
				//	pTile->ShowWidget();
			}
		}
	}
}

void ASummonerController::LButtonClick()
{
	bLButtonDown = true;

	FHitResult result;

	bool bHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
		false, result);

	PastProcess();
	CurrentProcess(result.GetActor());
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


