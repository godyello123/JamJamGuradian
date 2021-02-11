// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageUpUI.generated.h"

/**
 *
 */
UCLASS()
class MPSG_API UDamageUpUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* FireUpButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* iceUpButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* NormalUpButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* NormalDmgCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* FireDmgCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UTextBlock* IceDmgCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* NormalCostText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* FireCostText;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UTextBlock* IceCostText;

protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetFireDmgLevelText(int32 iLevel);
	void SetIceDmgLevelText(int32 iLevel);
	void SetNormalDmgLevelText(int32 iLevel);
	void AddFireDmgLevel();
	void AddIceDmgLevel();
	void AddNormalDmgLevel();
	void SetFireCostText(int32 iCost);
	void SetNormalCostText(int32 iCost);
	void SetIceCostText(int32 iCost);

public:
	UFUNCTION(BlueprintCallable)
	void FireUpButtonCallback();
	UFUNCTION(BlueprintCallable)
	void IceUpButtonCallback();
	UFUNCTION(BlueprintCallable)
	void NormalUpButtonCallback();
};
