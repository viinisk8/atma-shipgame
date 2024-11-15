#include "WeaponSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

UWeaponSystem::UWeaponSystem()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsReloading = false;
}

void UWeaponSystem::BeginPlay()
{
    Super::BeginPlay();
    CurrentAmmo = MaxAmmo;
}

void UWeaponSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponSystem::FireWeapon(FVector Origin, FVector TargetDirection, float Range)
{
    FVector EndPoint = Origin + (TargetDirection * Range);
    FHitResult HitResult;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Origin, EndPoint, ECC_Visibility, Params);

    if (bHit)
    {
        AActor* HitActor = HitResult.GetActor();
        if (HitActor)
        {
            // Verifica se o ator tem o HealthComponent
            if (UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>())
            {
                // Subtrai o dano do valor de Health diretamente
                HealthComp->Health -= ShotDamage;
                UE_LOG(LogTemp, Warning, TEXT("Shot hit %s for %f damage. Remaining Health: %f"), *HitActor->GetName(), ShotDamage, HealthComp->Health);
            }
        }
    }

    if (bDebugMode)
    {
        DrawDebugLine(GetWorld(), Origin, EndPoint, FColor::Red, false, DebugDuration, 0, 1.0f);
    }
}

void UWeaponSystem::HandleFire(FVector Origin, FVector TargetDirection)
{
    if (bIsReloading || CurrentAmmo <= 0)
    {
        StartReload();
        return;
    }

    FireWeapon(Origin, TargetDirection, FireRange);
    CurrentAmmo--;

    if (CurrentAmmo <= 0)
    {
        StartReload();
    }
}

bool UWeaponSystem::CanFire() const
{
    return !bIsReloading && CurrentAmmo > 0;
}

void UWeaponSystem::StartReload()
{
    bIsReloading = true;
    GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &UWeaponSystem::FinishReload, ReloadTime, false);
}

void UWeaponSystem::FinishReload()
{
    bIsReloading = false;
    CurrentAmmo = MaxAmmo;
    UE_LOG(LogTemp, Warning, TEXT("Reload complete. Ammo refilled."));
}

void UWeaponSystem::StopFiring()
{
    GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);
    bIsReloading = false;
}
