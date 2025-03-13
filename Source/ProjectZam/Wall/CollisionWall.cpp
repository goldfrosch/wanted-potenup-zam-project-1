// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionWall.h"

#include "Components/CollisionDetectComponent.h"
#include "Interfaces/IHttpResponse.h"


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

	TWeakObjectPtr<ACollisionWall> WeakThis = this;
	PoseSampleRequest.Callback = [WeakThis](FHttpRequestPtr Req, FHttpResponsePtr Res, const bool IsSuccess)
	{
		if (!IsSuccess)
		{
			UE_LOG(LogTemp, Error, TEXT("Pose Sample Request Failed"));
			return;
		}
		
		if (WeakThis.IsValid())
		{
			const FString JsonString = Res->GetContentAsString();
			
			ACollisionWall* StrongThis = WeakThis.Get();
			if (StrongThis)
			{
				UE_LOG(LogTemp, Display, TEXT("FEAT: %s"), *JsonString);
				StrongThis->CollisionDetectComponent->SetPoseData(JsonString);
				StrongThis->CollisionDetectComponent->SaveBonePositionsByImageCoordinates();
				StrongThis->CollisionDetectComponent->SaveDetectionPoints();
				StrongThis->Synchronized = true;
			}
		}
	};
	PoseSampleRequest.Path = "/pose/sample";

	FAPIUtil::GetMainAPI()->GetApi(this, PoseSampleRequest, PoseSampleResponse);

	SetMoveToTarget();
}

// Called every frame
void ACollisionWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Test Code
	CollisionDetectComponent->ChangeNormalizedPointsToPoints();

	if (bIsMoving && Synchronized)
	{
		// TODO : 이동 로직 고치기
		// 현재 위치
		FVector CurrentLocation = GetActorLocation();
		
		// 목표 위치까지 남은 거리
		float DistanceRemaining = (TargetLocation - StartLocation).Size(); // 거리 계산
		
		// 일정한 속도 계산 (2초 내 도착)
		float Speed = DistanceRemaining / 1.0f; 
		
		// 이동할 방향
		FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
		
		// 이동 실행
		FVector NewLocation = CurrentLocation + Direction * Speed * DeltaTime;
		SetActorLocation(NewLocation);

		// FVector NewLocation = GetActorLocation();

		// 목표 위치 도착 여부 확인
		if (FMath::Abs(NewLocation.X - TargetLocation.X) <= 20.0f)
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
	
	FVector HeadPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->HeadPos));
	FVector LeftShoulderPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->LeftShoulderPos));
	FVector RightShoulderPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->RightShoulderPos));
	FVector LeftElbowPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->LeftElbowPos));
	FVector RightElbowPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->RightElbowPos));
	FVector LeftHandPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->LeftHandPos));
	FVector RightHandPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->RightHandPos));
	FVector LeftHipPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->LeftHipPos));
	FVector RightHipPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->RightHipPos));
	FVector LeftKneePos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->LeftKneePos));
	FVector RightKneePos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->RightKneePos));
	FVector LeftFootPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->LeftFootPos));
	FVector RightFootPos = CollisionDetectComponent->UnNormalizePoint(CollisionDetectComponent->NormalizePoint(InCollisionDetectComponent->RightFootPos));

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
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Collision Detected"));
		}
	}
}

