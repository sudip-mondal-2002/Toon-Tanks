// Sudip Mondal 


#include "TankGameModeBase.h"


void ATankGameModeBase::HandleGameStart() 
{
    
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon) 
{
    
}

void ATankGameModeBase::ActorDied(AActor* DeadActor) 
{
    // Checl what type of Actor died. If Turret, tally. If Player -> go to lose condition.
    UE_LOG(LogTemp, Warning, TEXT("A Pawn Died"));
}

void ATankGameModeBase::BeginPlay() 
{
    
}
