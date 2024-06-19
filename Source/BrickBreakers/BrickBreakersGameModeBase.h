// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BrickBreakersGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKERS_API ABrickBreakersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:
		ABrickBreakersGameModeBase();

		bool gameStarted;

		UPROPERTY(BlueprintReadOnly, Category = "Score")
			int32 Score;

		void AddScore(int32 Value);

		UFUNCTION(BlueprintCallable, Category = "Game")
		void StartGame();

		UFUNCTION(BlueprintCallable, Category = "Game")
		void EndGame();

		UFUNCTION(BlueprintCallable, Category = "Game")
		void RestartGame();

		void BrickDestroyed();


protected:
	void BeginPlay() override;

private:
	class UScoreWidget* ScoreWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UScoreWidget> ScoreWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> StartMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> EndMenuWidgetClass;

	class UUserWidget* StartMenuWidgetInstance;
	class UUserWidget* EndMenuWidgetInstance;

	int32 TotalBricks;
	int32 BricksDestroyed;

	void CheckGameWin();

};
