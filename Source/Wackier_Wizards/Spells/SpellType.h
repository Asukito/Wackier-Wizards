// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SpellType.generated.h"

UENUM(BlueprintType)
enum class SpellType : uint8
{
	HITSCAN UMETA(DisplayName = "Hitscan"),
	PROJECTILE UMETA(DisplayName = "Projectile"),
	BEAM UMETA(DisplayName = "Beam"),
	SCATTER UMETA(DisplayName = "Scatter"),
	SELF UMETA(DisplayName = "Self")
};