// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ENUM_StateOfShip.generated.h"

UENUM(BlueprintType)
enum class EStateOfShip : uint8
{
	Aiming      UMETA(DisplayName = "Aiming"),
	Reloading   UMETA(DisplayName = "Reloading")
	};
