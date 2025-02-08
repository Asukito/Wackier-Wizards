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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == EffectType::OVERTIME || type == EffectType::FOR_DURATION", EditConditionHides))
	float duration = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == EffectType::OVERTIME", EditConditionHides))
	float effectInterval = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EffectBonusType bonus = EffectBonusType::NONE;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bonus == EffectBonusType::BOUNCE | bonus == EffectBonusType::AOE", EditConditionHides))
	float bonusRange;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "bonus == EffectBonusType::AOE", EditConditionHides))
	float aoeInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool stackable = false;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//TObjectPtr<UNiagaraSystem> spellNiagara;
};
