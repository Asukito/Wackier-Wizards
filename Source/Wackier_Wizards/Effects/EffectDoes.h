// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EffectDoes.generated.h"

UENUM(BlueprintType)
enum class EffectDoes : uint8
{
	 DAMAGE UMETA(DisplayName = "Damage"),
	 DAMAGE_PERCENT UMETA(DisplayName = "Damage by % of Max Health"),
	 HEAL UMETA(DisplayName = "Heal"),
	 HEAL_PERCENT UMETA(DisplayName = "Heal by % of Max Health"),
	 INC_MAXHP UMETA(DisplayName = "Increase Max Health (%)"),
	 DEC_MAXHP UMETA(DisplayName = "Decrease Max Health (%)"),
	 INC_SPEED UMETA(DisplayName = "Increase Speed (%)"),
	 DEC_SPEED UMETA(DisplayName = "Decrease Speed (%)"),
	 DISABLE_ACTIONS UMETA(DisplayName = "Disable actions (stun, freeze, etc)")
};
