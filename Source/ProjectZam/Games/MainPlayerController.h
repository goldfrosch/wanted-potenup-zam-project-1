// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UScoreUI;

UCLASS()
class PROJECTZAM_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TObjectPtr<UScoreUI> ScoreUI;
	UPROPERTY()
	TObjectPtr<UUserWidget> LevelChangerUI;


protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Score", meta = (AllowPrivateAccess = true))
	TSubclassOf<UScoreUI> ScoreUIFactory;
	UPROPERTY(EditAnywhere, Category = "Score", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> LevelChangerUIFactory;	
};
