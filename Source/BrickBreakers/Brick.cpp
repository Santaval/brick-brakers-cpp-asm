// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "BrickBreakersGameModeBase.h"
#include <Kismet/GameplayStatics.h>

extern "C" int destroyedBlock(int type);
// Sets default values
ABrick::ABrick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SM_Brick = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brick Mesh"));
	RootComponent = SM_Brick;


	SM_Brick->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SM_Brick->SetCollisionProfileName(TEXT("BlockAll"));


}

// Called when the game starts or when spawned
void ABrick::BeginPlay()

{
	Super::BeginPlay();
	SetRandomMaterial();
	
}

// Called every frame
void ABrick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrick::Delete()
	
{
	if (hitsRemaining > 1)
	{
		hitsRemaining--;
		UE_LOG(LogTemp, Warning, TEXT("Destroyed: %d"), destroyedBlock(this->hitsRemaining));
		UMaterialInterface* RandomMaterial = BrickMaterials[hitsRemaining - 1];
		SM_Brick->SetMaterial(0, RandomMaterial);
		// Play destruction sound
		UE_LOG(LogTemp, Warning, TEXT("Hits Remaining: %d"), hitsRemaining);
		if (BounceSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, BounceSound, GetActorLocation());
		}
	}
	else
	{
		
		int rand = FMath::RandRange(0, 100);
		bool shouldSpawnPowerUp = rand < 20;
		

		if (PowerUpClass && shouldSpawnPowerUp)
		{
			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = GetActorRotation();
			FActorSpawnParameters SpawnParams;
			GetWorld()->SpawnActor<APowerUp>(PowerUpClass, SpawnLocation, SpawnRotation, SpawnParams);
		}
		else {
						UE_LOG(LogTemp, Warning, TEXT("No PowerUpClass set for %s"), *GetName());
		}

		ABrickBreakersGameModeBase* GameMode = Cast<ABrickBreakersGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->BrickDestroyed(this->type);
		}
		if (BreakingSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, BreakingSound, GetActorLocation());
		}
		Destroy();
	}
}


void ABrick::SetRandomMaterial()
{	
	// LOG MATERIALS 
	for (int32 i = 0; i < BrickMaterials.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Material: %s"), *BrickMaterials[i]->GetName());
	}
	if (SM_Brick && BrickMaterials.Num() > 0)
	{	
		//int32 brickType = gen_brick();
		int32 brickType = FMath::RandRange(0, BrickMaterials.Num() - 1);
		this->type = brickType;
		UMaterialInterface* RandomMaterial = BrickMaterials[brickType];
		hitsRemaining = brickType + 1;
		SM_Brick->SetMaterial(0, RandomMaterial);
	}
}
