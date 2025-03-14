// Fill out your copyright notice in the Description page of Project Settings.


#include "WallManager.h"

#include "CollisionWall.h"

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
	FString AnswerPath = FPaths::ProjectContentDir() + "Answer.txt";
	FString AnswerStringJson;
	FFileHelper::LoadFileToString(AnswerStringJson, *AnswerPath);
	
	// 2. Json을 파싱한다.
	
	
	// 3. 정답 파일을 기반으로 각 벽들을 생성한다.
	
	
	// 4. 각 벽들을 생성한 후, 전체 플레이 타임에 벽의 개수를 나눠서 각 벽이 생성되는 시간을 계산한다.
	SpawnRate = PlayTime / CollisionWalls.Num();
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AWallManager::SpawnWalls, SpawnRate, false, 0.0f);
}

void AWallManager::SpawnWalls()
{
	if (CollisionWalls.IsValidIndex(0))
	{
		ACollisionWall* Wall = CollisionWalls[0];
		Wall->SetMoveToTarget();
		CollisionWalls.RemoveAt(0);
	}
}

// Called every frame
void AWallManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

