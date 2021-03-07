// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../00Base/GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 *
 */
UCLASS()
class MPSG_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* WaveText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* WaveNumberText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* CountText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* ClockText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* GoldGemCountText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* FireGemCountText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* IceGemCountText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* GoldGemImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* FireGemImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* IceGemImage;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* DamageUpButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* UtilityUpButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UButton* SkipTimeButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UDamageUpUI* DamageUpUI;


protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);


public:
	void SetWaveNumber(int32 iWave);
	void SetIceGemCount(int32 iCount);
	void SetGoldGemCount(int32 iCount);
	void SetFireGemCount(int32 iCount);

public:
	UFUNCTION(BlueprintCallable)
	void DamageUpCallback();
	UFUNCTION(BlueprintCallable)
	void SkipButtonCallback();

public:
	void SetFireDmgLevel(int32 iLevel);
	void SetIceDmgLevel(int32 iLevel);
	void SetNormalDmgLevel(int32 iLevel);

public:
	void SetMonsterCountText(int32 iCount);
	void SetClock(int32 iMinute, int32 iSecond);
	void SpawnTile();


};
