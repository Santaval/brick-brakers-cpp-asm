#include "BrickGenerator.h"
#include "Brick.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABrickGenerator::ABrickGenerator()
{
    PrimaryActorTick.bCanEverTick = true;

    Rows = 10;       // Number of rows
    Columns = 7;     // Number of columns
    BrickSpacingX = 40.f; // Spacing between bricks in X
    BrickSpacingZ = 20.f;  // Spacing between bricks in Z
}

// Called when the game starts or when spawned
void ABrickGenerator::BeginPlay()
{
    Super::BeginPlay();

    if (BrickClass)
    {
        FVector StartLocation = GetActorLocation();

        for (int32 Row = 0; Row < Rows; ++Row)
        {
            for (int32 Col = 0; Col < Columns; ++Col)
            {
                FVector BrickLocation = StartLocation + FVector(Col * BrickSpacingX, 0, Row * BrickSpacingZ);
                GetWorld()->SpawnActor<ABrick>(BrickClass, BrickLocation, FRotator::ZeroRotator);
            }
        }
    }
}

// Called every frame
void ABrickGenerator::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
