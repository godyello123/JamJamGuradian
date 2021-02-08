// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TextRenderActor.h"
#include "TextRender_GemCount.generated.h"

/**
 * 
 */
UCLASS()
class MPSG_API ATextRender_GemCount : public ATextRenderActor
{
	GENERATED_BODY()

public:
	ATextRender_GemCount();

public:
	void SetText(FString& strText);
	void SetTextCount(int32 iCount);
};
