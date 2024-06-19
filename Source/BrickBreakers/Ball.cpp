#include "Ball.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Brick.h"
#include "BrickBreakersGameModeBase.h"
#include <Kismet/GameplayStatics.h>


ABall::ABall()
{
    PrimaryActorTick.bCanEverTick = false;

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

}

void ABall::Launch()
{
    // Dirección de la velocidad constante que deseas aplicar
    const FVector ConstantVelocityDirection = FVector(1.0f, 1.0f, 1.0f).GetSafeNormal(); // Normalizado para garantizar que la velocidad sea constante

    // Magnitud de la velocidad constante que deseas aplicar
    const float ConstantVelocityMagnitude = 1000.0f; // Ajusta este valor según la velocidad deseada

    // Aplicar la velocidad constante a la bola
    SM_Ball->SetPhysicsLinearVelocity(ConstantVelocityDirection * ConstantVelocityMagnitude, true);
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
		// cast to brick
        ABrick* brick = Cast<ABrick>(Other);
        // destroy brick
		brick->Delete();
        // bounce ball
        SM_Ball->AddImpulse(FVector(0, 0, -200), NAME_None, false);
	}
	else if (Other->ActorHasTag("BottomWall"))
	{   
        auto GameMode = Cast<ABrickBreakersGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
        if (GameMode)
        {
            GameMode->EndGame();
        }

	}

    else if (Other->ActorHasTag("Paddle"))
	{
		// paddle
		SM_Ball->AddImpulse(FVector(0, 0, 200), NAME_None, false);
	}


}




void ABall::controlImpulse(AActor* Other)
{   
    bool isToUp = SM_Ball->GetComponentVelocity().Z > 0;
    float ZImpulse;
    if (isToUp) {
        ZImpulse = 200 - SM_Ball->GetComponentVelocity().Z;
    }
    else {
        ZImpulse = (-200) - SM_Ball->GetComponentVelocity().Z;
    }


    // check wich wall the ball hit
    if (Other->ActorHasTag("RightWall")){
        // right wall
        SM_Ball->AddImpulse(FVector(-200, 0, ZImpulse), NAME_None, false);
    }
    else if (Other->ActorHasTag("LeftWall"))
    {
        // left wall
        SM_Ball->AddImpulse(FVector(200, 0, ZImpulse), NAME_None, false);
    }
    else if (Other->ActorHasTag("TopWall"))
    {
        // top wall
        SM_Ball->AddImpulse(FVector(0, 0, -200), NAME_None, false);
    }
}
