// Copyright Epic Games, Inc. All Rights Reserved.


#include "BrickBreakersGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ScoreWidget.h"
#include "Blueprint/UserWidget.h"
#include "Ball.h"
#include "Brick.h"

ABrickBreakersGameModeBase::ABrickBreakersGameModeBase()
{
	// Set default score
	Score = 0;
    gameStarted = false;
    TotalBricks = 0;
    BricksDestroyed = 0;
}

void ABrickBreakersGameModeBase::AddScore(int32 Value)
{
	Score += Value;

	// Update the score widget
	if (ScoreWidget)
	{
		ScoreWidget->UpdateScore(Score);
	}
}

void ABrickBreakersGameModeBase::BeginPlay()
{
    Super::BeginPlay();

}

void ABrickBreakersGameModeBase::StartGame()
{
    if (StartMenuWidgetInstance)
    {
        StartMenuWidgetInstance->RemoveFromViewport();
    }



     // Load Gameplay Level
    UGameplayStatics::OpenLevel(GetWorld(), FName("Gameplay"));
    gameStarted = true;

    // Show Score Widget
    if (ScoreWidget)
    {
        ScoreWidget = CreateWidget<UScoreWidget>(GetWorld(), ScoreWidgetClass);
        if (ScoreWidget)
        {
            ScoreWidget->AddToViewport();
        }
    }
}

void ABrickBreakersGameModeBase::EndGame()
{
    if (ScoreWidget)
    {
        ScoreWidget->RemoveFromViewport();
    }

    // Show End Menu
    if (EndMenuWidgetClass)
    {
        EndMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), EndMenuWidgetClass);
        if (EndMenuWidgetInstance)
        {
            EndMenuWidgetInstance->AddToViewport();
        }
    }
}

void ABrickBreakersGameModeBase::RestartGame()
{
    UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void ABrickBreakersGameModeBase::BrickDestroyed()
{
    BricksDestroyed++;
    CheckGameWin();
}

void ABrickBreakersGameModeBase::CheckGameWin()
{
    TArray<AActor*> Bricks;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABrick::StaticClass(), Bricks);
    TotalBricks = Bricks.Num();
    // log total bricks
    UE_LOG(LogTemp, Warning, TEXT("Total Bricks: %d"), TotalBricks);
      

    if (TotalBricks <= 1)
	{
		EndGame();
	}
}