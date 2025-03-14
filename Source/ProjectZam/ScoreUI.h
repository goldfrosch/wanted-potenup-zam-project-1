// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTZAM_API UScoreUI : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateScore(int32 score);

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ScoreText;
};
