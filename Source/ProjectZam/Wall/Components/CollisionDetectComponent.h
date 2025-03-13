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
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// 우선 입력을 저장해야함.
	FString JsonString;

private:
	UFUNCTION()
	void CalculateLines();
	
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	float Width = 720.0f;
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	float Height = 1280.0f;
	UPROPERTY(EditAnywhere, Category = "Pose", meta = (AllowPrivateAccess = "true"))
	FPoseDataEntry PoseData;

	TArray<FVector2D, FVector2D> Lines;
};
