// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "BuffUI.generated.h"

/**
 *
 */
UCLASS()
class MPSG_API UBuffUI : public UUserWidget
{
	GENERATED_BODY()

private:
	class AGuardian* m_pOwner;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* DmgBuff;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UImage* GageBuff;

	
protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetOwner(class AGuardian* pOnwer);

public:
	void DmgBuffEnable(bool bEnable);
	void GageBuffEnabld(bool bEnable);

};
