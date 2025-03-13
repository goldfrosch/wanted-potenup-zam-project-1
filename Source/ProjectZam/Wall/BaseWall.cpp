// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWall.h"

#include "Components/CollisionDetectComponent.h"


// Sets default values
ABaseWall::ABaseWall()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionDetectComponent = CreateDefaultSubobject<UCollisionDetectComponent>(TEXT("CollisionDetectComponent"));
}

// Called when the game starts or when spawned
void ABaseWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
