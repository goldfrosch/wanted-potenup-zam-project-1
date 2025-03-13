// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWall.generated.h"

UCLASS()
class PROJECTZAM_API ABaseWall : public APawn
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float headRadius = 150.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float lineThickness = 10.0f;
};
