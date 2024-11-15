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


#include "HealthComponent.h"
#include "TimerManager.h"

//     -------------------------------------------------------------------------------------------
UHealthComponent::UHealthComponent()
{
  PrimaryComponentTick.bCanEverTick = true;

  //
  Health = 100.0f;
  MaxHealth = 100.0f; 
  TimeSinceLastDamage = 0.0f;
  TimeToRegenerate = 5.0f;
  RegeneratePerSecond = 10.0f;
  bCanRegenerate = false;
}

//     -------------------------------------------------------------------------------------------
void UHealthComponent::BeginPlay()
{
  Super::BeginPlay();

  //
  Health = MaxHealth;
}

//     -------------------------------------------------------------------------------------------
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  
  TimeSinceLastDamage += DeltaTime;
  
  if (TimeSinceLastDamage >= TimeToRegenerate)
  {
    bCanRegenerate = true;
  }
  
  if (bCanRegenerate && Health < MaxHealth)
  {
    RegenerateHealth(DeltaTime);
  }
}

//     -------------------------------------------------------------------------------------------
void UHealthComponent::TakeDamage(float DamageAmount)
{
  Health -= DamageAmount;
  Health = FMath::Clamp(Health, 0.0f, MaxHealth);
  
  TimeSinceLastDamage = 0.0f;
  bCanRegenerate = false;

  UE_LOG(LogTemp, Warning, TEXT("Health after damage: %f"), Health);
}

//     -------------------------------------------------------------------------------------------
void UHealthComponent::RegenerateHealth(float DeltaTime)
{
  Health += RegeneratePerSecond * DeltaTime;
  Health = FMath::Clamp(Health, 0.0f, MaxHealth);
  
  if (Health >= MaxHealth)
  {
    bCanRegenerate = false;
  }

  UE_LOG(LogTemp, Warning, TEXT("Regenerating Health: %f"), Health);
}

//     -------------------------------------------------------------------------------------------