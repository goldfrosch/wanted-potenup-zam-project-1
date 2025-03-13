// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionWall.h"

#include "Components/CollisionDetectComponent.h"


// Sets default values
ACollisionWall::ACollisionWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACollisionWall::BeginPlay()
{
	Super::BeginPlay();

	TargetLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	CollisionDetectComponent->SaveBonePositionsByImageCoordinates();
	CollisionDetectComponent->SaveDetectionPoints();

	
}

// Called every frame
void ACollisionWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMoving)
	{
		// 현재 위치
		FVector CurrentLocation = GetActorLocation();

		// 목표 위치까지 남은 거리
		float DistanceRemaining = TargetLocation.X - StartLocation.X;

		// 2초 내 도착해야 하므로 가속도 계산
		float Acceleration = DistanceRemaining / 2.0f;

		// 속도 업데이트
		Speed += Acceleration * DeltaTime;

		// 이동할 위치 계산
		FVector NewLocation = CurrentLocation;
		NewLocation.X += Speed * DeltaTime;

		// 이동 실행
		SetActorLocation(NewLocation);

		// 목표 위치 도착 여부 확인
		if (FMath::Abs(NewLocation.X - TargetLocation.X) <= KINDA_SMALL_NUMBER)
		{
			// 목표 위치에 도착하면 충돌 검사를 시작한다.
			TryCollisionDetect();
		}
	}
}

void ACollisionWall::SetMoveToTarget()
{
	bIsMoving = true;
}

void ACollisionWall::TryCollisionDetect()
{
	UCollisionDetectComponent* InCollisionDetectComponent = Cast<ABaseWall>(GetWorld()->GetFirstPlayerController()->GetPawn())->CollisionDetectComponent;
	
	FVector HeadPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->HeadPos);
	FVector LeftShoulderPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->LeftShoulderPos);
	FVector RightShoulderPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->RightShoulderPos);
	FVector LeftElbowPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->LeftElbowPos);
	FVector RightElbowPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->RightElbowPos);
	FVector LeftHandPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->LeftHandPos);
	FVector RightHandPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->RightHandPos);
	FVector LeftHipPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->LeftHipPos);
	FVector RightHipPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->RightHipPos);
	FVector LeftKneePos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->LeftKneePos);
	FVector RightKneePos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->RightKneePos);
	FVector LeftFootPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->LeftFootPos);
	FVector RightFootPos = CollisionDetectComponent->UnNormalizePoint(InCollisionDetectComponent->RightFootPos);

	TArray<FVector> Points;
	
	Points.Add(HeadPos);
	Points.Add(LeftShoulderPos);
	Points.Add(RightShoulderPos);
	Points.Add(LeftElbowPos);
	Points.Add(RightElbowPos);
	Points.Add(LeftHandPos);
	Points.Add(RightHandPos);
	Points.Add(LeftHipPos);
	Points.Add(RightHipPos);
	Points.Add(LeftKneePos);
	Points.Add(RightKneePos);
	Points.Add(LeftFootPos);
	Points.Add(RightFootPos);

	CollisionDetectComponent->ChangeNormalizedPointsToPoints();
	
	for (auto& Point : Points)
	{
		if (CollisionDetectComponent->CheckCollision(Point))
		{
			UE_LOG(LogTemp, Warning, TEXT("Collision Detected"));
			break;
		}
	}
}

