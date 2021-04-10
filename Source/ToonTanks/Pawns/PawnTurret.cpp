// Sudip Mondal

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PawnTank.h"
#include "TimerManager.h"

//Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this,0));
}
//Called Every Frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!PlayerPawn || ReturnDistanceFromPlayer()>FireRange){
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition() 
{
    if (!PlayerPawn)
    {
        return;
    }
    if (ReturnDistanceFromPlayer()<=FireRange)
    {
        Fire();
    }
}

float APawnTurret::ReturnDistanceFromPlayer() 
{
    if (!PlayerPawn)
    {
        return 0.f;
    }

    float Distance = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
    return Distance;
}

void APawnTurret::HandleDestruction() 
{
	Super::HandleDestruction();
    Destroy();
}