// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "SpawnGuardianTileUI.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API USpawnGuardianTileUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* KnightButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* MageButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* ArcherButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* WarriorButton;

private:
	class ATile_SpawnGuardian* Owner;

public:
	void SetOwner(class ATile_SpawnGuardian* _Owner);

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SpawnKnight();
	void SpawnMage();
	void SpawnArcher();
	void SpawnWarrior();
private:
	UFUNCTION(BlueprintCallable)
	void KnightButtonCallback();
	UFUNCTION(BlueprintCallable)
	void MageButtonCallback();
	UFUNCTION(BlueprintCallable)
	void ArcherButtonCallback();
	UFUNCTION(BlueprintCallable)
	void WarriorButtonCallback();

};
