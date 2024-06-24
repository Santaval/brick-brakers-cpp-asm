// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"
//extern "C" INT64 genBrick();	
UCLASS()
class BRICKBREAKERS_API ABrick : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABrick();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	int hitsRemaining;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SM_Brick;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Brick")
	UStaticMeshComponent* BrickMesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	TArray<UMaterialInterface*> BrickMaterials;

	// Sound to play upon destruction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* BounceSound;
	// Sound to play upon destruction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* BreakingSound;

	// ABrick no continene ningun mimebro onHit solucionar el error
	
	void Delete();
	void SetRandomMaterial();



};
