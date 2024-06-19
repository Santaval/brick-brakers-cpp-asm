#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

extern "C" INT64 calcBallImpulse(INT64);

UCLASS()
class BRICKBREAKERS_API ABall : public AActor
{
    GENERATED_BODY()

public:
    ABall();

    void Launch();

    bool ballLaunched;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* SM_Ball;


public:
    virtual void Tick(float DeltaTime) override;

    UFUNCTION()
    UStaticMeshComponent* GetBall();

    virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
    
    void controlImpulse(AActor* Other);

};
