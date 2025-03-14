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

	if (LevelChangerUIFactory)
	{
		LevelChangerUI = CreateWidget<UUserWidget>(this, LevelChangerUIFactory);
		LevelChangerUI->AddToViewport();
		LevelChangerUI->SetVisibility(ESlateVisibility::Hidden);		
	}
}
