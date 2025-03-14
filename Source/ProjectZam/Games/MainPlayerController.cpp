#include "MainPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "ProjectZam/ScoreUI.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ScoreUIFactory)
	{
		ScoreUI = CreateWidget<UScoreUI>(this, ScoreUIFactory);
		ScoreUI->AddToViewport();
	}
}
