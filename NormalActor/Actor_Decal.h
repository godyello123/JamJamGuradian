// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "Actor_Decal.generated.h"

UCLASS()
class MPSG_API AActor_Decal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Decal();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		UDecalComponent* Decal;

private:
	bool m_bDecal;
	bool m_bDecalSkillOn;

public:
	void SetDecalSkillOn(bool bEnable);
	bool GetDecalSkillOn() const;

public:
	void EnableDecal(bool bEnable);
	bool IsEnableDecal() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
