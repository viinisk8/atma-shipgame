#include "AtmaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "../Enemies/Enemy.h"

// Construtor
AAtmaGameMode::AAtmaGameMode()
{
  PrimaryActorTick.bCanEverTick = true;
}

// BeginPlay: Configura o Timer para spawnar os inimigos
void AAtmaGameMode::BeginPlay()
{
  Super::BeginPlay();

  // Verifica se a classe do inimigo foi atribuída
  if (EnemyClass)
  {
    // Inicia o Timer para spawnar os inimigos de acordo com o intervalo configurado
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAtmaGameMode::SpawnEnemies, SpawnInterval, true);
  }
  else
  {
    UE_LOG(LogTemp, Warning, TEXT("EnemyClass is not set in GameMode!"));
  }
}

// Função que spawna os inimigos
void AAtmaGameMode::SpawnEnemies()
{
  // Obter a referência ao jogador
  APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
  if (!PlayerPawn) return;

  for (int32 i = 0; i < EnemyCount; ++i)
  {
    // Defina uma posição aleatória em um raio ao redor do jogador, mas no mesmo eixo horizontal
    FVector SpawnLocation = PlayerPawn->GetActorLocation() + FVector(FMath::RandRange(-500, 500), 0.0f, FMath::RandRange(-500, 500));
    FRotator SpawnRotation = FRotator::ZeroRotator;

    // Spawna o inimigo
    AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, SpawnLocation, SpawnRotation);

    // Configura o inimigo para perseguir o jogador automaticamente (ou configure a lógica no próprio inimigo)
    if (SpawnedEnemy)
    {
      // Defina qualquer configuração específica que precise para o inimigo aqui
    }
  }
}


