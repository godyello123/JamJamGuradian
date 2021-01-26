// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "Actor_Gem.generated.h"

UCLASS()
class MPSG_API AActor_Gem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Gem();

protected:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
	//UPROPERTY(Category = Particle, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//	UParticleSystemComponent* particle;

protected:
	int32 iValue;

public:
	void SetValue(int32 Value);
	int32 GetValue() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
