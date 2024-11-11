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

#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerShip.h"
//
#include "PlayerShipController.generated.h"


UCLASS()
class ATMA_API APlayerShipController : public APlayerController
{
	GENERATED_BODY()

public:
	// methods
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void AddMovementY(float Value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void AddMovementX(float Value);

	UFUNCTION(BlueprintCallable, Category = "Movement")
	void RotateShip();

	void CreatePlayerShipReference();
	// Properties

	UPROPERTY(VisibleAnywhere, Category = "Reference")
	APlayerShip* PlayerShip;

protected:
	virtual void BeginPlay() override;
	
};
