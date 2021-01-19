// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "GameFramework/Actor.h"
#include "Tile_SpawnGuardian.generated.h"

UCLASS()
class MPSG_API ATile_SpawnGuardian : public AActor
{
	GENERATED_BODY()
	
public:
	ATile_SpawnGuardian();

public:
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
	UPROPERTY(Category = MouseClick, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool bClicked;
	UPROPERTY(Category = Type, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		EElementalType Elemental;


public:
	void Click(bool _Click);
	bool IsClick() const;

public:
	void SetElementalType(EElementalType eType);
	EElementalType GetElementalType() const;


public:
	void SpawnGuardian(EGuardianType eType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void ShowUI(bool bShow);


};
