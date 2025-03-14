// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreUI.h"

#include "Components/TextBlock.h"

void UScoreUI::UpdateScore(int32 score)
{
	ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), score)));
}
