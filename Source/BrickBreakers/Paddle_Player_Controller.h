// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Ball.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Paddle_Player_Controller.generated.h"

/**
 * 
 */
UCLASS()
class BRICKBREAKERS_API APaddle_Player_Controller : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void SetupInputComponent() override;

protected:
	virtual void BeginPlay() override;
	void MoveHorizontal(float AxisValue);
	void LaunchBall();

	UPROPERTY()
		ABall* Ball;

	
};
