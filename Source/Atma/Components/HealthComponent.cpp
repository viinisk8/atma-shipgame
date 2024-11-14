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
//     Date      : 2024-11-14                                                   ------------------
//     Author    : viniciusteologia@gmail.com                                   ------------------
//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------


#include "HealthComponent.h"
#include "TimerManager.h"

//     -------------------------------------------------------------------------------------------
UHealthComponent::UHealthComponent()
{
  PrimaryComponentTick.bCanEverTick = true;
  MaxHealth = Health;
  TimeSinceLastDamage = 0.0f;
  bCanRegenerate = false;
}

//     -------------------------------------------------------------------------------------------
void UHealthComponent::BeginPlay()
{
  Super::BeginPlay();
  Health = MaxHealth;
}

//     -------------------------------------------------------------------------------------------
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  
  if (TimeSinceLastDamage < TimeToRegenerate)
  {
    TimeSinceLastDamage += DeltaTime;
    bCanRegenerate = false;
  }
  else
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

  UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

//     -------------------------------------------------------------------------------------------
void UHealthComponent::RegenerateHealth(float DeltaTime)
{
  Health += RegeneratePerSecond * DeltaTime;
  Health = FMath::Clamp(Health, 0.0f, MaxHealth);

  UE_LOG(LogTemp, Warning, TEXT("Regenerating Health: %f"), Health);
}

//     -------------------------------------------------------------------------------------------