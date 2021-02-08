// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../00Base/GameInfo.h"
#include "GameFramework/Character.h"
#include "Summoner.generated.h"


UCLASS()
class MPSG_API ASummoner : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASummoner();

private:
	class UAnim_Summoner* Animation;

private:
	class ATileManager* TileManager;

public:
	class ATileManager* GetTileManager() const;

private:
	void CreateCamera(FVector& vLoc,FRotator& vRot);

private:
	class AFreeCam* FreeCam;

private:
	float YawOffset;

public:
	void SetOffsetYaw(float Rot);


public:
	class UAnim_Summoner* GetAnimation() const;
	void ChangeAnim(ESummonerAnimType eType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveHorizontal(float fScale);
	void MoveVertical(float fScale);

};
