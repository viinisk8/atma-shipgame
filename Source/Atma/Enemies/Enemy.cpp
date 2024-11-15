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
//     Date      : 2024-11-11                                                   ------------------
//     Author    : viniciusteologia@gmail.com                                   ------------------
//     -------------------------------------------------------------------------------------------
//     -------------------------------------------------------------------------------------------


#include "Enemy.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	//
	PrimaryActorTick.bCanEverTick = true;

	//
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
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//
	MoveTowardsPlayer();
	AttackPlayer();
}

//     -------------------------------------------------------------------------------------------
void AEnemy::MoveTowardsPlayer()
{
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn)
	{
		FVector Direction = (PlayerPawn->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Direction, 1.0f);
	}
}

//     -------------------------------------------------------------------------------------------
void AEnemy::AttackPlayer()
{
	//
}
