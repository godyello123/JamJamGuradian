// Fill out your copyright notice in the Description page of Project Settings.


#include "SummonerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../Character/Guardian/Summoner.h"
#include "../Character/Guardian/Guardian.h"
#include "../Character/Monster/Monster.h"
#include "../Tile/Tile_SpawnGuardian.h"
#include "../NormalActor/Actor_Decal.h"
#include "../Spell/Spell.h"

ASummonerController::ASummonerController()
{
	
}

void ASummonerController::BeginPlay()
{
	ClickedActor = nullptr;

	bGuardianSkill = false;
}

void ASummonerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bGuardianSkill)
	{
		SkillLocation(DeltaTime);
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

void ASummonerController::SkillLocation(float fDeltaTime)
{
	FHitResult	result;

	bool	bHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
		false, result);

	if (bHit)
	{
		AGuardian* pGuardian = Cast<AGuardian>(RClickedActor);
		if (pGuardian)
		{
			AActor_Decal* pDecal = pGuardian->GetDecal();
			if (pDecal)
			{
				if(pDecal->IsEnableDecal())
					pDecal->SetActorLocation(result.ImpactPoint);
			}
		}
	}
}

void ASummonerController::SkillOn()
{
}

void ASummonerController::SkillforActor(AActor * pActor,const  FVector& vLoc)
{
	RClickedActor = pActor;

	if (IsValid(RClickedActor))
	{
		if (RClickedActor->Tags.Num() > 0)
		{
			if (RClickedActor->Tags[0] == "Guardian")
			{
				AGuardian* pGuardian = Cast<AGuardian>(RClickedActor);

				if (pGuardian)
				{
					if (pGuardian->GetState().fTierGageMax_3 <= pGuardian->GetState().fTierGage_3)
					{
						AActor_Decal* pDecal = pGuardian->GetDecal();

						if (pDecal)
						{
							pDecal->EnableDecal(true);
							pDecal->SetActorLocation(vLoc);
						}
					}
				}
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
	bGuardianSkill = true;
	//해당 티어 가디언 스킬 만들어주기
	FHitResult result;

	bool bHit = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,
		false, result);

	SkillforActor(result.GetActor(), result.ImpactPoint);
}

void ASummonerController::RButtonRelease()
{
	bRButtonDown = false;
	bGuardianSkill = false;

	AGuardian* pGuardian = Cast<AGuardian>(RClickedActor);

	if (pGuardian)
	{
		if (pGuardian->GetDecal())
		{
			AActor_Decal* pDecal = pGuardian->GetDecal();

			if (pDecal)
			{
				pDecal->SetDecalSkillOn(true);
			}
		}
	}
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


