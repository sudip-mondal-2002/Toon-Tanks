// Sudip Mondal

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

//Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}
//Called Every Frame
void APawnTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition() 
{
    UE_LOG(LogTemp,Warning,TEXT("Checked fire condition"));
}
