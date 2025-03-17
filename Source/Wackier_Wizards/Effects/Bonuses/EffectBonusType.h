// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EffectBonusType.generated.h"

UENUM(BlueprintType)
enum class EffectBonusType : uint8
{
	NONE UMETA(DisplayName = "None"),
	BOUNCE UMETA(DisplayName = "Bounce")
};
