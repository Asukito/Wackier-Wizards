// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SpellType.generated.h"

UENUM(BlueprintType)
enum class SpellType : uint8
{
	HITSCAN UMETA(DisplayName = "Hitscan"),
	HITSCAN_AOE UMETA(DisplayName = "Hitscan AOE"),
	PROJECTILE UMETA(DisplayName = "Projectile"),
	PROJECTILE_AOE UMETA(DisplayName = "Projectile AOE"),
	LOCAL_AOE UMETA(DisplayName = "Local AOE"),
	SELF UMETA(DisplayName = "Self")
};