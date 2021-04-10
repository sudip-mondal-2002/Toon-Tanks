// Sudip Mondal 


#include "TankGameModeBase.h"
#include "../Pawns/PawnTank.h"
#include "../Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "../PlayerControllers/PlayerControllerBase.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"


void ATankGameModeBase::BeginPlay() 
{
    Super::BeginPlay();
    HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    // Check what type of Actor died. If Turret, tally. If Player -> go to lose condition.
    if(DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }

    }
    else if(APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
    {
        DestroyedTurret->HandleDestruction();

        if(--TargetTurrets == 0)
        {
            HandleGameOver(true);
        }
    }
}

void ATankGameModeBase::HandleGameStart() 
{
    // Get Turret and Player Pawn details.
    TargetTurrets = GetTargetTurretCount();
    PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
    PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this,0));
    GameStart();
    if(PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);

            FTimerHandle PlayerEnableHandle;
            FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
            GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
            UE_LOG(LogTemp,Warning,TEXT("hello"));
        }

}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    GameOver(PlayerWon);    
}

int32 ATankGameModeBase::GetTargetTurretCount() 
{
    TArray<AActor *> TurretActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
    return TurretActors.Num();

}
