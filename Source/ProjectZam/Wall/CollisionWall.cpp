// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionWall.h"

#include "Components/CollisionDetectComponent.h"
#include "Interfaces/IHttpResponse.h"
#include "ProjectZam/PlayerWall.h"


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

	CollisionDetectComponent->WallWidth *= WidthScale;
	CollisionDetectComponent->WallHeight *= HeightScale;

	TargetLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	// 목표 지점까지의 거리
	const float Distance = FVector::Distance(TargetLocation, StartLocation);

	// 이동 속도 (유닛/초)
	// MovementDuration이 0이 되지 않도록 주의하거나 체크 로직을 넣어주세요.
	if (MovementDuration > 0.0f)
	{
		Speed = Distance / MovementDuration;
	}
	else
	{
		Speed = 0.0f;
	}
}

// Called every frame
void ACollisionWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// (예시) 평소 충돌 포인트 변환 로직
	CollisionDetectComponent->ChangeNormalizedPointsToPoints();

	// bIsMoving이면 매 프레임 이동
	if (bIsMoving && Synchronized)
	{
		// 1) 현재까지 경과된 시간
		const float CurrentTime = GetWorld()->GetTimeSeconds();
		const float ElapsedTime = CurrentTime - StartTime;

		// 2) 0~1 사이의 보간 비율 alpha = 경과시간 / 전체이동시간
		float Alpha = 0.0f;
		if (MovementDuration > 0.f)
		{
			Alpha = ElapsedTime / MovementDuration;
		}

		// 3) 만약 Alpha가 1.0 이상이면 "완료 시점"이라는 의미
		if (Alpha >= 1.0f)
		{
			// 정확히 타깃 위치로 이동 (스냅)
			SetActorLocation({TargetLocation.X, StartLocation.Y, StartLocation.Z});
            
			// 이동 완료 처리
			bIsMoving = false;
            
			// 목표 위치 도착 시 충돌 검사
			TryCollisionDetect();
		}
		else
		{
			// 4) 아직 완료 시간이 되지 않았다면, 
			//    StartLocation ~ TargetLocation를 Alpha 비율만큼 선형보간
			float NewX = FMath::Lerp(StartLocation.X, TargetLocation.X, Alpha);
			FVector NewLocation = FVector(NewX, StartLocation.Y, StartLocation.Z);
			SetActorLocation(NewLocation);
		}
	}
}

void ACollisionWall::SetMoveToTarget(FPoseDataEntry& PoseData)
{
	for (int32 i = 0; i < PoseData.Pose.Num(); ++i)
	{
		// Log
		UE_LOG(LogTemp, Warning, TEXT("PoseData[%d] PersonId: %d"), i, PoseData.Pose[i].PersonId);
		for (int32 j = 0; j < PoseData.Pose[i].Keypoints.Num(); ++j)
		{
			UE_LOG(LogTemp, Warning, TEXT("PoseData[%d] Keypoint[%d] Id: %d"), i, j, PoseData.Pose[i].Keypoints[j].Id);
			UE_LOG(LogTemp, Warning, TEXT("PoseData[%d] Keypoint[%d] X: %f"), i, j, PoseData.Pose[i].Keypoints[j].X);
			UE_LOG(LogTemp, Warning, TEXT("PoseData[%d] Keypoint[%d] Y: %f"), i, j, PoseData.Pose[i].Keypoints[j].Y);
			UE_LOG(LogTemp, Warning, TEXT("PoseData[%d] Keypoint[%d] Confidence: %f"), i, j, PoseData.Pose[i].Keypoints[j].Confidence);
		}
	}
	CollisionDetectComponent->SetPoseDataHard(PoseData);
	CollisionDetectComponent->SaveBonePositionsByImageCoordinates();
	CollisionDetectComponent->SaveDetectionPoints();
	// 이동 시작할 때, 현재 시간과 위치를 저장
	StartTime = GetWorld()->GetTimeSeconds();
	StartLocation = GetActorLocation();
    
	// 이제부터 Tick에서 이동 로직을 수행하게끔 플래그 on
	bIsMoving = true;
	Synchronized = true;
}

void ACollisionWall::UnSetMove()
{
	bIsMoving = false;
	Synchronized = false;
}

void ACollisionWall::AddScore()
{
	if (bAddedScore) return;
	auto* Target = Cast<APlayerWall>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Target)
	{
		Target->UpdateScore();
	}
}

void ACollisionWall::TryCollisionDetect()
{
	UCollisionDetectComponent* InCollisionDetectComponent = Cast<ABaseWall>(GetWorld()->GetFirstPlayerController()->GetPawn())->CollisionDetectComponent;
	
	TArray<FVector> Points;

	APlayerWall* PlayerWall = Cast<APlayerWall>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (PlayerWall)
	{
		Points = PlayerWall->points;
	}

	CollisionDetectComponent->ChangeNormalizedPointsToPoints();
	for (auto& Point : Points)
	{
		if (CollisionDetectComponent->CheckCollision(Point))
		{
			bIsDetected = true;
		}
	}

	auto* Target = Cast<APlayerWall>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (bIsDetected == false)
	{
		AddScore();
		bAddedScore = true;
		Target->SetPlaySound(Target->AddScoreSound);
	}
	else
	{
		Target->SetPlaySound(Target->HitSound);
	}
	
	Destroy();
}

