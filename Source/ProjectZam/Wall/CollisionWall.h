// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWall.h"
#include "ProjectZam/Utils/ApiUtil.h"
#include "CollisionWall.generated.h"

UCLASS()
class PROJECTZAM_API ACollisionWall : public ABaseWall
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACollisionWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetMoveToTarget();
	void AddScore();
private:
	void TryCollisionDetect();
	
	bool bIsMoving = false;
	FVector TargetLocation = FVector::ZeroVector;
	FVector StartLocation = FVector::ZeroVector;
	// float Speed;

	FApiRequest PoseSampleRequest;
	FApiResponse PoseSampleResponse;
	bool Synchronized = false;

	bool bIsDetected = false;
	bool bAddedScore = false;
};
