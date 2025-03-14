#pragma once

#include "CoreMinimal.h"
#include "JsonExportStruct.generated.h"

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

// 최상위 JSON 배열을 감싸는 구조체
USTRUCT(BlueprintType)
struct FPoseWrapper
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Pose")
	TArray<FPoseDataEntry> Poses;
};