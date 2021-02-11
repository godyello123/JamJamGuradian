// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GuardianUI.generated.h"

/**
 *
 */
UCLASS()
class MPSG_API UGuardianUI : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* NormalLevelUpButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* FireLevelUpButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UButton* IceLevelUpButton;

	class AGuardian* m_pOwner;


protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetOwner(class AGuardian* pOnwer);


public:
	UFUNCTION(BlueprintCallable)
	void NormalLevelUpButtonCallback();
	UFUNCTION(BlueprintCallable)
	void FireLevelUpButtonCallback();
	UFUNCTION(BlueprintCallable)
	void IceLevelUpButtonCallback();
};
