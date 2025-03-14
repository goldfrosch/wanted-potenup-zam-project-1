#include "CollisionDetectComponent.h"

#include "JsonObjectConverter.h"
#include "Evaluation/Blending/MovieSceneBlendType.h"

// Sets default values for this component's properties
UCollisionDetectComponent::UCollisionDetectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	// PrimaryComponentTick.bCanEverTick = true;
}
	
// Called when the game starts
void UCollisionDetectComponent::BeginPlay()
{
	Super::BeginPlay();
	
	LineLengths.Add(0.0f);
	LineLengths.Add(0.1f);
	LineLengths.Add(0.25f);
	LineLengths.Add(0.35f);
	LineLengths.Add(0.5f);
	LineLengths.Add(0.6f);
	LineLengths.Add(0.75f);
	LineLengths.Add(0.8f);
	LineLengths.Add(1.0f);
}

void UCollisionDetectComponent::SaveBonePositionsByImageCoordinates()
{
	// PoseData를 바탕으로 인체 구조에 맞게 선을 그리고 충돌을 체크할 점들의 위치를 계산한다.
	// 1. 데이터들을 로컬 변수로 복사한다.
	FKeypoint Head = GetKeypoint(0);
	HeadPos = FVector2D(Head.X, Head.Y);
	HeadPos.Y = Height - HeadPos.Y;
	FKeypoint LeftShoulder = GetKeypoint(5);
	LeftShoulderPos = FVector2D(LeftShoulder.X, LeftShoulder.Y);
	LeftShoulderPos.Y = Height - LeftShoulderPos.Y;
	FKeypoint RightShoulder = GetKeypoint(6);
	RightShoulderPos = FVector2D(RightShoulder.X, RightShoulder.Y);
	RightShoulderPos.Y = Height - RightShoulderPos.Y;
	FKeypoint LeftElbow = GetKeypoint(7);
	LeftElbowPos = FVector2D(LeftElbow.X, LeftElbow.Y);
	LeftElbowPos.Y = Height - LeftElbowPos.Y;
	FKeypoint RightElbow = GetKeypoint(8);
	RightElbowPos = FVector2D(RightElbow.X, RightElbow.Y);
	RightElbowPos.Y = Height - RightElbowPos.Y;
	FKeypoint LeftHand = GetKeypoint(9);
	LeftHandPos = FVector2D(LeftHand.X, LeftHand.Y);
	LeftHandPos.Y = Height - LeftHandPos.Y;
	FKeypoint RightHand = GetKeypoint(10);
	RightHandPos = FVector2D(RightHand.X, RightHand.Y);
	RightHandPos.Y = Height - RightHandPos.Y;
	FKeypoint LeftHip = GetKeypoint(11);
	LeftHipPos = FVector2D(LeftHip.X, LeftHip.Y);
	LeftHipPos.Y = Height - LeftHipPos.Y;
	FKeypoint RightHip = GetKeypoint(12);
	RightHipPos = FVector2D(RightHip.X, RightHip.Y);
	RightHipPos.Y = Height - RightHipPos.Y;
	FKeypoint LeftKnee = GetKeypoint(13);
	LeftKneePos = FVector2D(LeftKnee.X, LeftKnee.Y);
	LeftKneePos.Y = Height - LeftKneePos.Y;
	FKeypoint RightKnee = GetKeypoint(14);
	RightKneePos = FVector2D(RightKnee.X, RightKnee.Y);
	RightKneePos.Y = Height - RightKneePos.Y;
	FKeypoint LeftFoot = GetKeypoint(15);
	LeftFootPos = FVector2D(LeftFoot.X, LeftFoot.Y);
	LeftFootPos.Y = Height - LeftFootPos.Y;
	FKeypoint RightFoot = GetKeypoint(16);
	RightFootPos = FVector2D(RightFoot.X, RightFoot.Y);
	RightFootPos.Y = Height - RightFootPos.Y;
}

void UCollisionDetectComponent::SaveDetectionPoints()
{
	// A : 머리에서 목 까지의 선 : 하드 코딩 (0: 목 5: 왼쪽 어깨, 6: 오른쪽 어깨)
	FVector2D LineA = (LeftShoulderPos + RightShoulderPos) / 2 - HeadPos;
	CalculatePositionByLine(HeadPos, LineA);
	// B : 왼쪽 어깨에서 오른쪽 어깨 까지의 선
	FVector2D LineB = RightShoulderPos - LeftShoulderPos;
	CalculatePositionByLine(LeftShoulderPos, LineB);
	// C : 왼쪽 어깨에서 왼쪽 팔꿈치 까지의 선
	FVector2D LineC = LeftElbowPos - LeftShoulderPos;
	CalculatePositionByLine(LeftShoulderPos, LineC);
	// D : 오른쪽 어깨에서 오른쪽 팔꿈치 까지의 선
	FVector2D LineD = RightElbowPos - RightShoulderPos;
	CalculatePositionByLine(RightShoulderPos, LineD);
	// E : 왼쪽 팔꿈치에서 왼쪽 손목 까지의 선
	FVector2D LineE = LeftHandPos - LeftElbowPos;
	CalculatePositionByLine(LeftElbowPos, LineE);
	// F : 오른쪽 팔꿈치에서 오른쪽 손목 까지의 선
	FVector2D LineF = RightHandPos - RightElbowPos;
	CalculatePositionByLine(RightElbowPos, LineF);
	// G : 목에서 엉덩이 까지의 선
	FVector2D LineG = (LeftHipPos + RightHipPos) / 2 - (LeftShoulderPos + RightShoulderPos) / 2;
	CalculatePositionByLine((LeftShoulderPos + RightShoulderPos) / 2, LineG);
	// H : 왼쪽 엉덩이에서 오른쪽 엉덩이 까지의 선
	FVector2D LineH = RightHipPos - LeftHipPos;
	CalculatePositionByLine(LeftHipPos, LineH);
	// I : 왼쪽 엉덩이에서 왼쪽 무릎 까지의 선
	FVector2D LineI = LeftKneePos - LeftHipPos;
	CalculatePositionByLine(LeftHipPos, LineI);
	// J : 오른쪽 엉덩이에서 오른쪽 무릎 까지의 선
	FVector2D LineJ = RightKneePos - RightHipPos;
	CalculatePositionByLine(RightHipPos, LineJ);
	// K : 왼쪽 무릎에서 왼쪽 발목 까지의 선
	FVector2D LineK = LeftFootPos - LeftKneePos;
	CalculatePositionByLine(LeftKneePos, LineK);
	// L : 오른쪽 무릎에서 오른쪽 발목 까지의 선
	FVector2D LineL = RightFootPos - RightKneePos;
	CalculatePositionByLine(RightKneePos, LineL);
}

void UCollisionDetectComponent::CalculatePositionByLine(FVector2D Start, FVector2D LineVector)
{
	// 선의 시작점과 방향을 받아서, LineLengths에 있는 길이들을 이용하여 점을 계산한다.
	for (auto& LineLength : LineLengths)
	{
		FVector2D End = Start + LineVector * LineLength;
		// 해당 점을 정규화 시킨다. (0 ~ 1) 사이의 값으로 변환 (image size: 640x480)
		End = NormalizePoint(End);
		NormalizedPoints.Add(End);
	}
}

// 매 순간 위치가 바뀌므로, 정규화된 점을 실제 위치로 변환해주어야 한다.
void UCollisionDetectComponent::ChangeNormalizedPointsToPoints()
{
	// 정규화 된 점을 Wall의 크기로 변환
	Points.Empty();
	for (auto& NormalizedPoint : NormalizedPoints)
	{
		FVector Point = UnNormalizePoint(NormalizedPoint);

		// Test Code
		// Debug로 그려보기
		DrawDebugCircle(GetWorld(), Point, CollisionRadius, 32, FColor::Red, false, 0.0f, 0, 5.0f);
		
		Points.Add(Point);
	}
}

const FKeypoint& UCollisionDetectComponent::GetKeypoint(int32 KeypointId)
{
	if (!PoseMap.Contains(KeypointId))
	{
		UE_LOG(LogTemp, Warning, TEXT("KeypointId %d is not found in PoseMap"), KeypointId);
		PoseMap.Add(KeypointId, FKeypoint());
		return PoseMap[KeypointId];
	}
	return PoseMap[KeypointId];
}

FVector2D UCollisionDetectComponent::NormalizePoint(const FVector2D& Point) const
{
	return FVector2D(Point.X / Width, Point.Y / Height);
}

FVector UCollisionDetectComponent::UnNormalizePoint(const FVector2D& Point) const
{
	FVector Result = FVector(0, Point.X * WallWidth, Point.Y * WallHeight);

	// Point에 실제 위치 값을 넣어준다.
	Result.X += GetOwner()->GetActorLocation().X;
	Result.Y += GetOwner()->GetActorLocation().Y;
	Result.Z += GetOwner()->GetActorLocation().Z;
	
	return Result;
}

bool UCollisionDetectComponent::CheckCollision(const FVector& Point)
{
	DrawDebugCircle(GetWorld(), Point, 10.0f, 32, FColor::Green, false, 0.0f, 0, 5.0f);
	for (auto& WallPoint : Points)
	{
		if (FVector2D::Distance({WallPoint.Y, WallPoint.Z}, {Point.Y, Point.Z}) <= CollisionRadius)
		{
			return true;
		}
	}
	DrawDebugCircle(GetWorld(), Point, 10.0f, 32, FColor::Orange, false, 3.0f, 0, 5.0f);
	return false;
}

void UCollisionDetectComponent::SetPoseData(const FString& InJsonString)
{
	JsonString = InJsonString;

	FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &PoseData, 0, 0);

	for (auto& Pose : PoseData.Pose[0].Keypoints)
	{
		if (!PoseMap.Contains(Pose.Id))
		{
			PoseMap.Add(Pose.Id, Pose);
		}
		else
		{
			PoseMap[Pose.Id] = Pose;
		}
	}
}

void UCollisionDetectComponent::DrawDebugHeadCircle(const FVector& Center, const float Radius, const float LineThickness)
{
	const float AngleStep = 2.0f * PI / 32;
	FVector PrevPoint = Center + FVector(0.0f, Radius, 0.0f);
    
	for (int32 i = 1; i <= 32; i++)
	{
		float Angle = AngleStep * i;
		FVector NextPoint = Center + FVector(0.0f , FMath::Cos(Angle) * Radius, FMath::Sin(Angle) * Radius);
        
		DrawDebugLine(
			GetWorld(),
			PrevPoint,
			NextPoint,
			FColor::White,
			false,
			-1.0f,
			0,
			LineThickness
		);
        
		PrevPoint = NextPoint;
	}
}

void UCollisionDetectComponent::DrawDebugBodyLine(const FVector& Start, const FVector& End, const float LineThickness)
{
	DrawDebugLine(GetWorld(), Start, End, FColor::White, false, -1, 0, LineThickness);
}

void UCollisionDetectComponent::SetPoseDataHard(const FPoseDataEntry& InPoseData)
{
	PoseData = InPoseData;

	for (auto& Pose : PoseData.Pose[0].Keypoints)
	{
		if (!PoseMap.Contains(Pose.Id))
		{
			PoseMap.Add(Pose.Id, Pose);
		}
		else
		{
			PoseMap[Pose.Id] = Pose;
		}
	}
}
