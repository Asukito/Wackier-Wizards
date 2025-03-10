// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EffectType.generated.h"

UENUM(BlueprintType)
enum class EffectType : uint8
{
	//DoT, Heal Over Time, etc
	EMPTY UMETA(DisplayName = "Empty"),
	OVERTIME UMETA(DisplayName = "OverTime"),
	INSTANT UMETA(DisplayName = "Instant"),
	FOR_DURATION UMETA(DisplayName = "For Duration"),
	AURA UMETA(DisplayName = "Aura"),
	SHIELD UMETA(DisplayName = "Shield")
};
