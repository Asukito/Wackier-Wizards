// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SpellType.h"
#include "SpellData.generated.h"

class UNiagaraSystem;
class AProjectile;
class UEffectData;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != SpellType::SELF", EditConditionHides))
	int potency = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TObjectPtr<UEffectData>, float> effects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> spellNiagara;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	SpellType type = SpellType::HITSCAN;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE || type == SpellType::HITSCAN", EditConditionHides))
	float range = 0.0f;;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE", EditConditionHides))
	float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE", EditConditionHides))
	bool useGravity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isAOE;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "isAOE == true", EditConditionHides))
	float aoeRange = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type ==	SpellType::PROJECTILE", EditConditionHides))
	bool hasTrail;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "hasTrail == true", EditConditionHides))
	TObjectPtr<UEffectData> trailEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE || type == SpellType::HITSCAN", EditConditionHides))
	TObjectPtr<UNiagaraSystem> collisionNiagara;
};
