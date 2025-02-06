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
	SpellType type = SpellType::HITSCAN;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TObjectPtr<UEffectData>, float> effects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> spellNiagara;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::HITSCAN_AOE || type == SpellType::PROJECTILE_AOE || type == SpellType::PROJECTILE || type == SpellType::HITSCAN", EditConditionHides))
	float range = 0.0f;;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::HITSCAN_AOE || type == SpellType::PROJECTILE_AOE || type == SpellType::LOCAL_AOE", EditConditionHides))
	float aoeRange = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE_AOE || type == SpellType::PROJECTILE", EditConditionHides))
	float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE_AOE || type == SpellType::PROJECTILE", EditConditionHides))
	bool useGravity;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE_AOE || type == SpellType::PROJECTILE", EditConditionHides))
	TSubclassOf<AProjectile> projectileDefault;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::HITSCAN_AOE || type == SpellType::PROJECTILE_AOE || type == SpellType::PROJECTILE || type == SpellType::HITSCAN", EditConditionHides))
	TObjectPtr<UNiagaraSystem> collisionNiagara;
};
