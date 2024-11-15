//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------
//     █████╗ ████████╗███╗   ███╗ █████╗      ██████╗  █████╗ ███╗   ███╗██╗███╗   ██╗ ██████╗ 
//     ██╔══██╗╚══██╔══╝████╗ ████║██╔══██╗    ██╔════╝ ██╔══██╗████╗ ████║██║████╗  ██║██╔════╝ 
//     ███████║   ██║   ██╔████╔██║███████║    ██║  ███╗███████║██╔████╔██║██║██╔██╗ ██║██║  ███╗
//     ██╔══██║   ██║   ██║╚██╔╝██║██╔══██║    ██║   ██║██╔══██║██║╚██╔╝██║██║██║╚██╗██║██║   ██║
//     ██║  ██║   ██║   ██║ ╚═╝ ██║██║  ██║    ╚██████╔╝██║  ██║██║ ╚═╝ ██║██║██║ ╚████║╚██████╔╝
//     ╚═╝  ╚═╝   ╚═╝   ╚═╝     ╚═╝╚═╝  ╚═╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝
//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------
//     Project   : AtmaGamingTest                                               ------------------
//     Date      : 2024-11-09                                                   ------------------
//     Author    : viniciusteologia@gmail.com                                   ------------------
//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------


#include "AtmaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../Enemies/Enemy.h"

//     -------------------------------------------------------------------------------------------
AAtmaGameMode::AAtmaGameMode()
{
  PrimaryActorTick.bCanEverTick = true;
}

//     -------------------------------------------------------------------------------------------
void AAtmaGameMode::BeginPlay()
{
  Super::BeginPlay();
  
  if (EnemyClass)
  {
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAtmaGameMode::SpawnEnemies, SpawnInterval, true);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("EnemyClass is not set in GameMode!"));
  }
}

//     -------------------------------------------------------------------------------------------
void AAtmaGameMode::SpawnEnemies()
{
  APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
  if (!PlayerPawn) return;

  for (int32 i = 0; i < EnemyCount; ++i)
  {
    FVector SpawnLocation = PlayerPawn->GetActorLocation() + FVector(FMath::RandRange(-500, 500), 0.0f, FMath::RandRange(-500, 500));
    FRotator SpawnRotation = FRotator::ZeroRotator;
    
    AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, SpawnRotation);
    
  }
}

//     -------------------------------------------------------------------------------------------
