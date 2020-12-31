// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../00Base/GameInfo.h"
#include "GameFramework/Character.h"
#include "FreeCam.generated.h"

UENUM(BlueprintType, Meta = (Bitflags))
enum class EFreeCamDir : uint8
{
	None,
	Up,
	Down,
	Right,
	Left,
	UpRight,
	UpLeft,
	DownRight,
	DownLeft
};



UCLASS()
class MPSG_API AFreeCam : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFreeCam();

protected:
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* Arm;

private:
	EFreeCamDir CamDir;
	bool bChasePlayer;
	class ASummoner* Summoner;

public:
	void SetSummoner(class ASummoner* Sum);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void MoveHorizontal(float fScale);
	void MoveVertical(float fScale);


};
