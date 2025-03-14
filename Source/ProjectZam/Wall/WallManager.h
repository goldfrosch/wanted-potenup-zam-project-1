// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WallManager.generated.h"

UCLASS()
class PROJECTZAM_API AWallManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWallManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnWalls();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TArray<class ACollisionWall*> CollisionWalls;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	UPROPERTY()
	float SpawnRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	float PlayTime = 0.0f;
};
