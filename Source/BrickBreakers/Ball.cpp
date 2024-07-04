#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Brick.h"
#include "BrickBreakersGameModeBase.h"
#include <Kismet/GameplayStatics.h>
extern "C" double calc_zimpulse(double velocityZ);

ABall::ABall()
{
    PrimaryActorTick.bCanEverTick = true;

    SM_Ball = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SM_Ball"));
    RootComponent = SM_Ball;

    SM_Ball->SetSimulatePhysics(true);
    SM_Ball->SetEnableGravity(false);
    SM_Ball->SetConstraintMode(EDOFMode::XZPlane);
    SM_Ball->SetLinearDamping(0.0f);
    SM_Ball->SetAngularDamping(0.0f);
    SM_Ball->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SM_Ball->SetCollisionProfileName(TEXT("PhysicsActor"));
    ballLaunched = false;
}

void ABall::BeginPlay()
{
    Super::BeginPlay();
}

void ABall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (ballLaunched)
    {
        MaintainConstantVelocity();
    }
}

void ABall::Launch()
{
    UE_LOG(LogTemp, Warning, TEXT("Launch Ball"));
    const FVector ConstantVelocityDirection = FVector(1.0f, 1.0f, 1.0f).GetSafeNormal();
    const float ConstantVelocityMagnitude = DesiredVelocityMagnitude;
    SM_Ball->AddImpulse(ConstantVelocityDirection * ConstantVelocityMagnitude, NAME_None, true);
    ballLaunched = true;
}

UStaticMeshComponent* ABall::GetBall()
{
    return SM_Ball;
}

void ABall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    if (Other->ActorHasTag("Wall"))
    {
        controlImpulse(Other);
    }
    else if (Other->ActorHasTag("Brick"))
    {
        ABrick* brick = Cast<ABrick>(Other);
        brick->Delete();
        SM_Ball->AddImpulse(FVector(0, 0, -200), NAME_None, false);
    }
    else if (Other->ActorHasTag("BottomWall"))
    {
        auto GameMode = Cast<ABrickBreakersGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
        if (GameMode && GameMode->lives > 1)
        {
            GameMode->lives--;
            GameMode->AddScore(0);
            this->SetActorLocation(FVector(0, 0, 100));
            SM_Ball->SetPhysicsLinearVelocity(FVector(0, 0, 0));
            ballLaunched = false;
        }
        else
        {
            GameMode->EndGame();
        }
    }
    else if (Other->ActorHasTag("Paddle"))
    {
        SM_Ball->AddImpulse(FVector(0, 0, 200), NAME_None, false);
    }
}

void ABall::controlImpulse(AActor* Other)
{
    float velocityZ = SM_Ball->GetComponentVelocity().Z;
    float ZImpulse = static_cast<float>(calc_zimpulse(static_cast<double>(velocityZ)));

    if (Other->ActorHasTag("RightWall"))
    {
        SM_Ball->AddImpulse(FVector(-200, 0, ZImpulse), NAME_None, false);
    }
    else if (Other->ActorHasTag("LeftWall"))
    {
        SM_Ball->AddImpulse(FVector(200, 0, ZImpulse), NAME_None, false);
    }
    else if (Other->ActorHasTag("TopWall"))
    {
        SM_Ball->AddImpulse(FVector(0, 0, -200), NAME_None, false);
    }
}

void ABall::MaintainConstantVelocity()
{
    FVector CurrentVelocity = SM_Ball->GetPhysicsLinearVelocity();
    FVector NormalizedVelocity = CurrentVelocity.GetSafeNormal();
    FVector DesiredVelocity = NormalizedVelocity * DesiredVelocityMagnitude;

    SM_Ball->SetPhysicsLinearVelocity(DesiredVelocity);
}
