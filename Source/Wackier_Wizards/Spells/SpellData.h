// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpellType.h"
#include "SpellData.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API USpellData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString name = " ";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float cooldown = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float duration = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int potency = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	SpellType type = SpellType::HITSCAN;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::HITSCAN_AOE || type == SpellType::PROJECTILE_AOE || type == SpellType::PROJECTILE || type == SpellType::HITSCAN", EditConditionHides))
	float range = 0.0f;;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::HITSCAN_AOE || type == SpellType::PROJECTILE_AOE || type == SpellType::LOCAL_AOE", EditConditionHides))
	float aoeRange = 0.0f;
};
