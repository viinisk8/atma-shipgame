#include "HealthComponent.h"
#include "TimerManager.h"

UHealthComponent::UHealthComponent()
{
  PrimaryComponentTick.bCanEverTick = true;

  Health = 100.0f; // Valor inicial padrão
  MaxHealth = 100.0f; 
  TimeSinceLastDamage = 0.0f;
  TimeToRegenerate = 5.0f; // Tempo de espera padrão para começar a regenerar
  RegeneratePerSecond = 10.0f; // Taxa de regeneração por segundo
  bCanRegenerate = false;
}

void UHealthComponent::BeginPlay()
{
  Super::BeginPlay();
  Health = MaxHealth;
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

  // Atualiza o tempo desde o último dano
  TimeSinceLastDamage += DeltaTime;

  // Checa se pode começar a regenerar
  if (TimeSinceLastDamage >= TimeToRegenerate)
  {
    bCanRegenerate = true;
  }

  // Se puder regenerar e a saúde não estiver no máximo
  if (bCanRegenerate && Health < MaxHealth)
  {
    RegenerateHealth(DeltaTime);
  }
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
  Health -= DamageAmount;
  Health = FMath::Clamp(Health, 0.0f, MaxHealth);

  // Reseta o tempo de regeneração
  TimeSinceLastDamage = 0.0f;
  bCanRegenerate = false;

  UE_LOG(LogTemp, Warning, TEXT("Health after damage: %f"), Health);
}

void UHealthComponent::RegenerateHealth(float DeltaTime)
{
  // Calcula a nova saúde baseada no tempo
  Health += RegeneratePerSecond * DeltaTime;
  Health = FMath::Clamp(Health, 0.0f, MaxHealth);

  // Interrompe a regeneração se atingir o máximo
  if (Health >= MaxHealth)
  {
    bCanRegenerate = false;
  }

  UE_LOG(LogTemp, Warning, TEXT("Regenerating Health: %f"), Health);
}
