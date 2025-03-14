// Fill out your copyright notice in the Description page of Project Settings.


#include "WallManager.h"

#include "CollisionWall.h"
#include "JsonObjectConverter.h"
#include "Blueprint/UserWidget.h"
#include "Components/CollisionDetectComponent.h"
#include "ProjectZam/Games/MainPlayerController.h"

// Sets default values
AWallManager::AWallManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWallManager::BeginPlay()
{
	Super::BeginPlay();

	// 1. 정답 파일을 읽어온다.
	FString AnswerPath = FPaths::ProjectContentDir() + "Answer.json";
	UE_LOG(LogTemp, Warning, TEXT("AnswerPath: %s"), *AnswerPath);
	FString AnswerStringJson;
	FFileHelper::LoadFileToString(AnswerStringJson, *AnswerPath);
	
	// 2. Json을 파싱한다.
	FJsonObjectConverter::JsonObjectStringToUStruct(AnswerStringJson, &PoseWrapper, 0, 0);
	
	// 4. 정답 파일을 기반으로 벽의 index를 계산한다.
	UE_LOG(LogTemp, Warning, TEXT("PoseWrapper Pose Num: %d"), PoseWrapper.Poses.Num());

	for (int i = 0; i < WallNum; ++i) {
		int index = std::round(i * (PoseWrapper.Poses.Num() - 1) / (WallNum - 1));  // 균일 간격 계산
		Indices.push_back(index);
	}

	for (int i = 0; i < Indices.size(); ++i) {
		UE_LOG(LogTemp, Warning, TEXT("Indices[%d]: %d"), i, Indices[i]);
	}
		
	// 4. 각 벽들을 생성한다.
	for (int i = 0; i < WallNum; ++i) {
		ACollisionWall* Wall = GetWorld()->SpawnActor<ACollisionWall>(WallClass);
		Wall->SetActorLocation(FVector(13080.0f, 0.0f, 440.0f));
		Wall->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
		Wall->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		CollisionWalls.Add(Wall);
	}

	for (int i = 0; i < WallNum ; ++i)
	{
		ACollisionWall* Wall = GetWorld()->SpawnActor<ACollisionWall>(WallClass);
		Wall->SetActorLocation(FVector(0.0f, 500.0f, 500.0f));
		Wall->SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
		Wall->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
		ImageWalls.Add(Wall);
	}
	
	// 5. 각 벽들을 생성한 후, 전체 플레이 타임에 벽의 개수를 나눠서 각 벽이 생성되는 시간을 계산한다.
	SpawnRate = PlayTime / WallNum;
	UE_LOG(LogTemp, Warning, TEXT("SpawnRate: %f"), SpawnRate);
	SpawnWalls();
}
	
void AWallManager::SpawnWalls()
{
	if (ImageWall)
	{
		ImageWall->Destroy();
	}

	if (CollisionWalls.IsValidIndex(0))
	{
		ACollisionWall* Wall = CollisionWalls[0];
		Wall->SetMoveToTarget(PoseWrapper.Poses[Indices[Index]]);
		CollisionWalls.RemoveAt(0);

		ImageWall = ImageWalls[0];
		ImageWall->SetMoveToTarget(PoseWrapper.Poses[Indices[Index]]);
		ImageWall->UnSetMove();
		ImageWall->CollisionDetectComponent->CollisionRadius = 10.0f;
		ImageWalls.RemoveAt(0);
		
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AWallManager::SpawnWalls, SpawnRate, false);
		Index++;
	}
	else
	{
		auto* controller = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
		if (controller)
		{
			controller->LevelChangerUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

// Called every frame
void AWallManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
