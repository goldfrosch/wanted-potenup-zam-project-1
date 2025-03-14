// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utils/ApiUtil.h"
#include "Wall/BaseWall.h"
#include "PlayerWall.generated.h"

UCLASS()
class PROJECTZAM_API APlayerWall : public ABaseWall
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerWall();

protected:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

public:
	void ConvertAndSaveCoord();
	void DrawBody();

	void UpdateScore();
	void SetPlaySound(class USoundWave* sound);
public:
	FApiRequest PoseSampleRequest;
	FApiResponse PoseSampleResponse;
	
	TArray<FVector2D> normalizedPoints;
	TArray<FVector> points;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sound")
	class UAudioComponent* SoundInstance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	class USoundWave* AddScoreSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	class USoundWave* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	int32 score = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	TSubclassOf<class UScoreUI> ScoreUIFactory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	class UScoreUI* ScoreUI;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	TSubclassOf<class UUserWidget> LevelChangeUIFactory;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Score")
	class UUserWidget* LevelChangeUI;
};
