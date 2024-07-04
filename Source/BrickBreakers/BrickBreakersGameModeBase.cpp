#include "BrickBreakersGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.h"
#include "Brick.h"

extern "C" int calc_score(int brickType);

ABrickBreakersGameModeBase::ABrickBreakersGameModeBase()
{
    // Set default score
    Score = 0;
    gameStarted = false;
    TotalBricks = 0;
    BricksDestroyed = 0;
    lives = 1;
}

void ABrickBreakersGameModeBase::AddScore(int32 Value)
{
    Score += Value;


        UScoreWidget* ScoreWidgetInstanceCasted = Cast<UScoreWidget>(ScoreWidgetInstance);
        if (ScoreWidgetInstanceCasted)
        {   
            UE_LOG(LogTemp, Warning, TEXT("Score Widget Updated"));
            ScoreWidgetInstanceCasted->UpdateScore(Score, lives);
        }
  
}

void ABrickBreakersGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (ScoreWidgetClass)
    {
        ScoreWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), ScoreWidgetClass);
        if (ScoreWidgetInstance)
        {
            ScoreWidgetInstance->AddToViewport();
            UE_LOG(LogTemp, Warning, TEXT("Score Widget Created Successfully"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to Create Score Widget"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ScoreWidgetClass is not set"));
    }
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


}

void ABrickBreakersGameModeBase::EndGame()
{

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
    gameStarted = false;
    lives = 1;
    Score = 0;
    BricksDestroyed = 0;
    TotalBricks = 0;
}

void ABrickBreakersGameModeBase::BrickDestroyed(int type)
{
    BricksDestroyed++;
    int calculatedScore = calc_score(type);
    AddScore(calculatedScore);
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
