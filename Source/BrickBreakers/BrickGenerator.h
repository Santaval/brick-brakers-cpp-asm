// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BrickGenerator.generated.h"

UCLASS()
class BRICKBREAKERS_API ABrickGenerator : public AActor
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    ABrickGenerator();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(EditAnywhere, Category = "Generation")
    TSubclassOf<class ABrick> BrickClass;

    UPROPERTY(EditAnywhere, Category = "Generation")
    int32 Rows;

    UPROPERTY(EditAnywhere, Category = "Generation")
    int32 Columns;

    UPROPERTY(EditAnywhere, Category = "Generation")
    float BrickSpacingX;

    UPROPERTY(EditAnywhere, Category = "Generation")
    float BrickSpacingZ;

    UPROPERTY(EditAnywhere, Category = "Generation")
    float BrickSpacing;
};
