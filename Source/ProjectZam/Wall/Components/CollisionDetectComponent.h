// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionDetectComponent.generated.h"

USTRUCT(BlueprintType)
struct FKeypoint
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	int32 Id;

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	float X;

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	float Y;

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	float Confidence;
};

USTRUCT(BlueprintType)
struct FPersonPose
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	int32 PersonId;

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	TArray<FKeypoint> Keypoints;
};

USTRUCT(BlueprintType)
struct FPoseDataEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	FString Status;

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	TArray<FPersonPose> Pose;

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	FString Timestamp;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTZAM_API UCollisionDetectComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCollisionDetectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// 우선 입력을 저장해야함.
	FString JsonString;

	UFUNCTION()
	void SaveBonePositionsByImageCoordinates();
	UFUNCTION()
	void SaveDetectionPoints();
	UFUNCTION()
	void CalculatePositionByLine(FVector2D Start, FVector2D LineVector);
	UFUNCTION()
	void ChangeNormalizedPointsToPoints();
	UFUNCTION()
	const FKeypoint& GetKeypoint(int32 KeypointId) const;
	UFUNCTION()
	FVector2D NormalizePoint(const FVector2D& Point) const;
	UFUNCTION()
	FVector UnNormalizePoint(const FVector2D& Point) const;

	// 디버그 라인 그리기 함수
	void DrawDebugHeadCircle(const FVector& Center, const float Radius, const float LineThickness);
	void DrawDebugBodyLine(const FVector& Start, const FVector& End, const float LineThickness);
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	float Width = 640.0f;
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	float Height = 480.0f;

	// Wall의 크기에 따라 조절되어야 함
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	float WallWidth = Width;
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	float WallHeight = Height;
	
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	FPoseDataEntry PoseData;

	TArray<FVector2D> NormalizedPoints;
	TArray<FVector> Points;

	TArray<float> LineLengths;

public:
	FVector2D HeadPos;
	FVector2D LeftShoulderPos;
	FVector2D RightShoulderPos;
	FVector2D LeftElbowPos;
	FVector2D RightElbowPos;
	FVector2D LeftHandPos;
	FVector2D RightHandPos;
	FVector2D LeftHipPos;
	FVector2D RightHipPos;
	FVector2D LeftKneePos;
	FVector2D RightKneePos;
	FVector2D LeftFootPos;
	FVector2D RightFootPos;
};
