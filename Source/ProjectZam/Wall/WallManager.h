// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectZam/JsonExportStruct.h"
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
	FPoseWrapper PoseWrapper;
	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
	UPROPERTY()
	float SpawnRate = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	float PlayTime = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	int32 WallNum = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	int32 Index = 0;

	std::vector<int32> Indices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall")
	TSubclassOf<class ACollisionWall> WallClass;
};
