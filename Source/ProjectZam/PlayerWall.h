// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:
	TArray<FVector2D> normalizedPoints;
	TArray<FVector> points;
};
