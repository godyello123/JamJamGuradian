// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "Actor_Spline.generated.h"


UCLASS()
class MPSG_API AActor_Spline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Spline();

protected:
	UPROPERTY(Category = Spline, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USplineComponent* m_pSpline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FVector GetPathLocation(float fTime);


private:
	void SetSplineDurationTime(float fTime);
public:
	float GetSplineDurationTime() const;



};
