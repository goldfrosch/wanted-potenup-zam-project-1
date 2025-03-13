// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWall.h"

#include "Wall/Components/CollisionDetectComponent.h"


// Sets default values
APlayerWall::APlayerWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// DrawBody();
}

void APlayerWall::ConvertAndSaveCoord()
{
	// Save Normalize
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->HeadPos));
	
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftShoulderPos));
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightShoulderPos));
	
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftElbowPos));
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightElbowPos));
	
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftHandPos));
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightHandPos));
	
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftHipPos));
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightHipPos));
	
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftKneePos));
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightKneePos));
	
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftFootPos));
	normalizedPoints.Add(CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightFootPos));

	// Save Unnormalized Points
	for (int32 i = 0; i < normalizedPoints.Num(); i++)
	{
		points.Add(CollisionDetectComponent->UnNormalizePoint(normalizedPoints[i]));
	}
}

void APlayerWall::DrawBody()
{
	CollisionDetectComponent->SaveBonePositionsByImageCoordinates();
	ConvertAndSaveCoord();

	// 대가리
	CollisionDetectComponent->DrawDebugHeadCircle(points[0], headRadius, lineThickness);

	// 몸통
	CollisionDetectComponent->DrawDebugBodyLine(points[5], points[6], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[5], points[11], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[6], points[12], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[12], points[11], lineThickness);

	// 왼팔
	CollisionDetectComponent->DrawDebugBodyLine(points[5], points[7], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[7], points[9], lineThickness);

	// 오른팔
	CollisionDetectComponent->DrawDebugBodyLine(points[6], points[8], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[8], points[10], lineThickness);

	// 왼다리
	CollisionDetectComponent->DrawDebugBodyLine(points[11], points[13], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[13], points[15], lineThickness);

	// 오른다리
	CollisionDetectComponent->DrawDebugBodyLine(points[12], points[14], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[14], points[16], lineThickness);
}

