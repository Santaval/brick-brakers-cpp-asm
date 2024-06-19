// Fill out your copyright notice in the Description page of Project Settings.


#include "Paddle_Player_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Paddle.h"


void APaddle_Player_Controller::BeginPlay()
{	
	// Get camera actors
	TArray <AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);

	FViewTargetTransitionParams Params;
	if (CameraActors.Num() > 0)
	{
		SetViewTarget(CameraActors[0], Params);
	}

	// Get Ball
	TArray <AActor*> BallActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), BallActors);
	if (BallActors.Num() > 0)
	{
		Ball = Cast<ABall>(BallActors[0]);
	}
}

void APaddle_Player_Controller::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);

	InputComponent->BindAxis("MoveHorizontal", this, &APaddle_Player_Controller::MoveHorizontal);
	InputComponent->BindAction("LaunchBall", IE_Pressed, this, &APaddle_Player_Controller::LaunchBall);
}


void APaddle_Player_Controller::MoveHorizontal(float AxisValue)
{
	if (AxisValue != 0)
	{
		auto Paddle = Cast<APaddle>(GetPawn());
		if (Paddle)
		{
			Paddle->MoveHorizontal(AxisValue);
		}
	}
}

void APaddle_Player_Controller::LaunchBall()
{

	if (Ball && !Ball->ballLaunched)
	{
		Ball->Launch();
	}
}
