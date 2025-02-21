// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EffectType.h"
#include "EffectDoes.h"
#include "EffectBonusType.h"
#include "EffectData.generated.h"

class UNiagaraSystem;

UCLASS()
class WACKIER_WIZARDS_API UEffectData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString name = " ";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EffectType type = EffectType::OVERTIME;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EffectDoes does = EffectDoes::DAMAGE;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int strength = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool stackable = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> effectNiagara;

	//---- NOT INSTANT ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != EffectType::INSTANT", EditConditionHides))
	float duration = 10.0f;

	//---- OVERTIME ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == EffectType::OVERTIME", EditConditionHides))
	float effectInterval = 1.0f;

	//---- AURA ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == EffectType::AURA || type == EffectType::SHIELD", EditConditionHides))
	float auraSize;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == EffectType::AURA", EditConditionHides))
	bool isPerTick = false;

	//---- BONUS ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != EffectType::AURA || type != EffectType::SHIELD", EditConditionHides))
	EffectBonusType bonus = EffectBonusType::NONE;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bonus != EffectBonusType::NONE", EditConditionHides))
	float bonusRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bonus == EffectBonusType::AOE || EffectBonusType::TRAIL_EFFECT", EditConditionHides))
	float aoeInterval;
};
