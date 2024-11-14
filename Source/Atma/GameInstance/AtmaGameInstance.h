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

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "../Data/ENUM_StateOfShip.h"
//
#include "AtmaGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStateOfShipChanged, EStateOfShip, NewState);

UCLASS()
class ATMA_API UAtmaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// methods
	UFUNCTION(BlueprintCallable)
	void SetStateOfShip(EStateOfShip NewState);
	
	// Properties
	UPROPERTY(BlueprintReadWrite)
	EStateOfShip StateOfShip;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStateOfShipChanged OnStateOfShipChanged;

	
	
};
