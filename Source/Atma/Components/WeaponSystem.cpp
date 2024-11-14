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

#include "WeaponSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

//     -------------------------------------------------------------------------------------------
UWeaponSystem::UWeaponSystem()
{
    PrimaryComponentTick.bCanEverTick = true;
    bIsReloading = false;
}

//     -------------------------------------------------------------------------------------------
void UWeaponSystem::BeginPlay()
{
    Super::BeginPlay();

    CurrentAmmo = MaxAmmo;
}

//     -------------------------------------------------------------------------------------------
void UWeaponSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//     -------------------------------------------------------------------------------------------
void UWeaponSystem::FireWeapon(FVector Origin, FVector TargetDirection, float Range)
{
    FVector EndPoint = Origin + (TargetDirection * Range);
    FHitResult HitResult;
    
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    
    bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Origin, EndPoint, ECC_Visibility, Params);

    if (bHit)
    {
        if (HitResult.GetActor())
        {
            UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
        }
    }
    
    if (bDebugMode)
    {
        DrawDebugLine(GetWorld(), Origin, EndPoint, FColor::Red, false, DebugDuration, 0, 1.0f);
    }
}

//     -------------------------------------------------------------------------------------------
void UWeaponSystem::HandleFire()
{
    if (bIsReloading)
    {
        UE_LOG(LogTemp, Warning, TEXT("Weapon is reloading..."));
        return;
    }

    if (CurrentAmmo > 0)
    {
        APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

        if (PlayerController)
        {
            FVector WorldLocation;
            FVector WorldDirection;
            
            if (PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
            {
                FVector Origin = GetOwner()->GetActorLocation();
                FVector TargetDirection = FVector(WorldDirection.X, 0.0f, WorldDirection.Z).GetSafeNormal();
                FireWeapon(Origin, TargetDirection, FireRange);
                
                CurrentAmmo--;
                
                if (CurrentAmmo <= 0)
                {
                    StartReload();
                }
            }
        }
    }
    else
    {
        StartReload();
    }
}

//     -------------------------------------------------------------------------------------------
void UWeaponSystem::StartReload()
{
    bIsReloading = true;
    UE_LOG(LogTemp, Warning, TEXT("Reloading..."));
    
    GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &UWeaponSystem::FinishReload, ReloadTime, false);
}

//     -------------------------------------------------------------------------------------------
void UWeaponSystem::FinishReload()
{
    bIsReloading = false;
    CurrentAmmo = MaxAmmo;
    UE_LOG(LogTemp, Warning, TEXT("Reload complete. Ammo refilled."));
}

//     -------------------------------------------------------------------------------------------
