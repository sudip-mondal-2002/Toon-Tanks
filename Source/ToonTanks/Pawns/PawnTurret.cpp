// Sudip Mondal

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "PawnTank.h"
#include "TimerManager.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

    PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction() 
{
    // Call base pawn class HandleDestruction to play effects. 
    Super::HandleDestruction();
    Destroy();    
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(!PlayerPawn || ReturnDistanceToPlayer() > FireRange)
    {
        return;
    }

    RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition() 
{
    // If Player == null || is Dead THEN BAIL!!
    if(!PlayerPawn || !PlayerPawn->GetPlayerAlive())
    {
        return;
    }
    // IF Player IS in range THEN FIRE!! 
    if(ReturnDistanceToPlayer() <= FireRange)
    {
        Fire();
    }
   
}

float APawnTurret::ReturnDistanceToPlayer() 
{
    if (!PlayerPawn)
    {
        0.0f;
    }

    return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}
