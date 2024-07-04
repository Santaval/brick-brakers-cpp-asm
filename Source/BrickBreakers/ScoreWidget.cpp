#include "ScoreWidget.h"
#include "Components/TextBlock.h"

void UScoreWidget::UpdateScore(int32 Score, int32 lives)
{
    if (ScoreText)
    {
        ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d vidas: %d"), Score, lives)));
    }
   }