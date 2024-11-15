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

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Enemy.generated.h"

UCLASS()
class ATMA_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

public:    
	virtual void Tick(float DeltaTime) override;

	// Enemy components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* FloatingPawnMovement;

private:
	void MoveTowardsPlayer(); // Custom function for AI movement towards player
	void AttackPlayer(); // Custom function for automatic attack
};
