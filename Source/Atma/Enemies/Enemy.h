#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "../Components/WeaponSystem.h"
#include "../Player/PlayerShip.h" // Inclua este cabeçalho para reconhecer APlayerShip
//
#include "Enemy.generated.h"
// Se preferir usar uma declaração antecipada, substitua a inclusão por esta linha:
// class APlayerShip;

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

	void ResetFireCooldown();
	
	// Componentes e propriedades
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collision")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy AI")
	float DesiredDistanceToPlayer = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy AI")
	float MoveSpeed = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float DamageAmount = 10.0f;

private:
	void FollowPlayer();
  
  void AttackPlayer();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY()
	UWeaponSystem* WeaponSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireCooldown = 1.0f; // Tempo mínimo entre disparos em segundos

	FTimerHandle FireCooldownTimer;
	bool bCanFire = true;
};
