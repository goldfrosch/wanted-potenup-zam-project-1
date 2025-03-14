// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectZam/JsonExportStruct.h"
#include "CollisionDetectComponent.generated.h"

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
	
	UFUNCTION()
	void SaveBonePositionsByImageCoordinates();
	UFUNCTION()
	void SaveDetectionPoints();
	UFUNCTION()
	void CalculatePositionByLine(FVector2D Start, FVector2D LineVector);
	UFUNCTION()
	void ChangeNormalizedPointsToPoints();
	UFUNCTION()
	const FKeypoint& GetKeypoint(int32 KeypointId);
	UFUNCTION()
	FVector2D NormalizePoint(const FVector2D& Point) const;
	UFUNCTION()
	FVector UnNormalizePoint(const FVector2D& Point) const;
	UFUNCTION()
	bool CheckCollision(const FVector& Point);
	UFUNCTION()
	void SetPoseData(const FString& InJsonString);
	// 디버그 라인 그리기 함수
	void DrawDebugHeadCircle(const FVector& Center, const float Radius, const float LineThickness);
	void DrawDebugBodyLine(const FVector& Start, const FVector& End, const float LineThickness);
	void SetPoseDataHard(const FPoseDataEntry& InPoseData);

	UPROPERTY(EditAnywhere, Category = "Pose")
	float Width = 640.0f;
	UPROPERTY(EditAnywhere, Category = "Pose")
	float Height = 480.0f;

	// Wall의 크기에 따라 조절되어야 함
	UPROPERTY(EditAnywhere, Category = "Pose")
	float WallWidth = Width;
	UPROPERTY(EditAnywhere, Category = "Pose")
	float WallHeight = Height;
private:
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	FPoseDataEntry PoseData;
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	TMap<int32, FKeypoint> PoseMap;

	TArray<FVector2D> NormalizedPoints;
	TArray<FVector> Points;
	
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	TArray<float> LineLengths;
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	float CollisionRadius = 50.0f;
};
