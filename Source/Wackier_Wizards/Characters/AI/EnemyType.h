// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EnemyType.generated.h"

UENUM(BlueprintType)
enum class EnemyType : uint8
{
	//DoT, Heal Over Time, etc
	MELEE UMETA(DisplayName = "Melee"),
	RANGED UMETA(DisplayName = "Ranged")
};
