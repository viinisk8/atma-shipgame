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


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

//     -------------------------------------------------------------------------------------------
AEnemy::AEnemy()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    RootComponent = BoxComponent;
    BoxComponent->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
    BoxComponent->SetCollisionProfileName(TEXT("Pawn"));

    //
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    SkeletalMeshComponent->SetupAttachment(BoxComponent);

    //
    FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

//     -------------------------------------------------------------------------------------------
void AEnemy::BeginPlay()
{
    Super::BeginPlay();
    WeaponSystem = FindComponentByClass<UWeaponSystem>();
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
}

//     -------------------------------------------------------------------------------------------
void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    FollowPlayer();
    AttackPlayer();
}

//     -------------------------------------------------------------------------------------------
void AEnemy::FollowPlayer()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        float DistanceToPlayer = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
        if (DistanceToPlayer > DesiredDistanceToPlayer)
        {
            FVector Direction = (PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
            FVector NewLocation = GetActorLocation() + Direction * MoveSpeed;
            SetActorLocation(NewLocation);
            FRotator LookAtRotation = (PlayerPawn->GetActorLocation() - NewLocation).Rotation();
            SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));
        }
    }
}

//     -------------------------------------------------------------------------------------------
void AEnemy::AttackPlayer()
{
    if (WeaponSystem && bCanFire)
    {
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if (PlayerPawn)
        {
            float DistanceToPlayer = FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());

            if (DistanceToPlayer <= 500.0f)
            {
                FVector Origin = GetActorLocation();
                FVector DirectionToPlayer = (PlayerPawn->GetActorLocation() - Origin).GetSafeNormal();

                if (WeaponSystem->CanFire())
                {
                    WeaponSystem->HandleFire(Origin, DirectionToPlayer);
                    UE_LOG(LogTemp, Warning, TEXT("Enemy is firing at player"));
                    bCanFire = false;
                    
                    GetWorld()->GetTimerManager().SetTimer(FireCooldownTimer, this, &AEnemy::ResetFireCooldown, FireCooldown, false);
                }
            }
            else
            {
                WeaponSystem->StopFiring();
                UE_LOG(LogTemp, Warning, TEXT("Player out of range. Enemy stops firing."));
            }
        }
    }
}

//     -------------------------------------------------------------------------------------------
void AEnemy::ResetFireCooldown()
{
    bCanFire = true;
}

//     -------------------------------------------------------------------------------------------
void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {
        if (OtherActor->IsA(APlayerShip::StaticClass()))
        {
            UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, GetController(), this, nullptr);
            UE_LOG(LogTemp, Warning, TEXT("Collision with player: Applying damage."));
        }
    }
}

//     -------------------------------------------------------------------------------------------