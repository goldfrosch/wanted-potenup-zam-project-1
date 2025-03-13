// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWall.generated.h"

UCLASS()
class PROJECTZAM_API ABaseWall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UCollisionDetectComponent* CollisionDetectComponent;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
