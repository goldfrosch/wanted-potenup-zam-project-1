// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWall.h"

#include "ScoreUI.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Interfaces/IHttpResponse.h"
#include "Wall/Components/CollisionDetectComponent.h"


// Sets default values
APlayerWall::APlayerWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SoundInstance = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundInstance"));
}

// Called when the game starts or when spawned
void APlayerWall::BeginPlay()
{
	Super::BeginPlay();

	ScoreUI = Cast<UScoreUI>(CreateWidget(GetWorld(), ScoreUIFactory));
	if (ScoreUI)
	{
		ScoreUI->AddToViewport();
	}

	LevelChangeUI = CreateWidget(GetWorld(), LevelChangeUIFactory);
	if (LevelChangeUI)
	{
		LevelChangeUI->AddToViewport();
		LevelChangeUI->SetVisibility(ESlateVisibility::Hidden);
	}
	
	
	for (int32 i = 0 ; i < 13; i++)
	{
		normalizedPoints.Add(FVector2d::Zero());
		points.Add(FVector::Zero());
	}
}

// Called every frame
void APlayerWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TWeakObjectPtr<APlayerWall> weakThis = this;
	PoseSampleRequest.Callback = [weakThis](FHttpRequestPtr Req, FHttpResponsePtr Res, const bool IsSuccess) {
		if (weakThis.IsValid())
		{
			auto* StrongThis = weakThis.Get();
			if (StrongThis)
			{
				if (!IsSuccess) return;
				const FString JsonString = Res->GetContentAsString();
				StrongThis->CollisionDetectComponent->SetPoseData(JsonString);
			}
		}
	};
	PoseSampleRequest.Path = "/pose/mock";
	FAPIUtil::GetMainAPI()->GetApi(this, PoseSampleRequest, PoseSampleResponse);
	DrawBody();
}

void APlayerWall::ConvertAndSaveCoord()
{
	// Save Normalize
	normalizedPoints[0] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->HeadPos));
	
	normalizedPoints[1] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftShoulderPos));
	normalizedPoints[2] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightShoulderPos));
	
	normalizedPoints[3] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftElbowPos));
	normalizedPoints[4] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightElbowPos));
	
	normalizedPoints[5] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftHandPos));
	normalizedPoints[6] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightHandPos));
	
	normalizedPoints[7] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftHipPos));
	normalizedPoints[8] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightHipPos));
	
	normalizedPoints[9] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftKneePos));
	normalizedPoints[10] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightKneePos));
	
	normalizedPoints[11] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->LeftFootPos));
	normalizedPoints[12] = (CollisionDetectComponent->NormalizePoint(CollisionDetectComponent->RightFootPos));

	// Save Unnormalized Points
	for (int32 i = 0; i < normalizedPoints.Num(); i++)
	{
		points[i] = CollisionDetectComponent->UnNormalizePoint(normalizedPoints[i]);
	}
}

void APlayerWall::DrawBody()
{
	CollisionDetectComponent->SaveBonePositionsByImageCoordinates();
	ConvertAndSaveCoord();

	// 대가리
	CollisionDetectComponent->DrawDebugHeadCircle(points[0], headRadius, lineThickness);

	// 몸통
	CollisionDetectComponent->DrawDebugBodyLine(points[1], points[2], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[1], points[7], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[2], points[8], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[8], points[7], lineThickness);

	// 왼팔
	CollisionDetectComponent->DrawDebugBodyLine(points[1], points[3], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[3], points[5], lineThickness);

	// 오른팔
	CollisionDetectComponent->DrawDebugBodyLine(points[2], points[4], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[4], points[6], lineThickness);

	// 왼다리
	CollisionDetectComponent->DrawDebugBodyLine(points[7], points[9], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[9], points[11], lineThickness);

	// 오른다리
	CollisionDetectComponent->DrawDebugBodyLine(points[8], points[10], lineThickness);
	CollisionDetectComponent->DrawDebugBodyLine(points[10], points[12], lineThickness);
}

void APlayerWall::UpdateScore()
{
	score++;
	ScoreUI->UpdateScore(score);
}

void APlayerWall::SetPlaySound(class USoundWave* sound)
{
	SoundInstance->SetSound(sound);
	SoundInstance->Play();
}

