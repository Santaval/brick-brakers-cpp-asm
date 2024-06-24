// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "BrickBreakersGameModeBase.h"
#include <Kismet/GameplayStatics.h>
extern "C" int gen_brick();
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
		ABrickBreakersGameModeBase* GameMode = Cast<ABrickBreakersGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->BrickDestroyed();
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
		int32 brickType = gen_brick();
		UMaterialInterface* RandomMaterial = BrickMaterials[brickType];
		hitsRemaining = brickType + 1;
		SM_Brick->SetMaterial(0, RandomMaterial);
	}
}
