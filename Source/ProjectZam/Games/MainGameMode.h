// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectZam/Utils/ApiUtil.h"
#include "MainGameMode.generated.h"

UCLASS()
class PROJECTZAM_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	FApiRequest PoseSampleRequest;
	FApiResponse PoseSampleResponse;
};
