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
class WACKIER_WIZARDS_API USpellData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
//Spell DataAsset that contains any spell stats, and is used to Decorate the spell during creation
public:
	//---- ALL TYPES ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString name = " ";
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int manaCost = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<TObjectPtr<UEffectData>, float> effects;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> spellNiagara;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ESpellType type = ESpellType::HITSCAN;

	///---- NON-BEAM ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != ESpellType::BEAM", EditConditionHides))
	float cooldown = 0.0f;

	//---- NON-SELF ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != ESpellType::SELF", EditConditionHides))
	int potency = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != ESpellType::SELF", EditConditionHides))
	float range = 0.0f;;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != ESpellType::SELF", EditConditionHides))
	TObjectPtr<UNiagaraSystem> collisionNiagara;

	//---- SCATTER ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::SCATTER", EditConditionHides))
	bool isHitscan = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::SCATTER", EditConditionHides))
	int scatterAmount;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::SCATTER", EditConditionHides), meta = (ClampMin = "0.0", ClampMax = "90"))
	float scatterRange;

	//---- PROJECTILE ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE || (type == ESpellType::SCATTER && isHitscan == false)", EditConditionHides))
	float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE || (type == ESpellType::SCATTER && isHitscan == false)", EditConditionHides), meta = (ClampMin = "0.1", ClampMax = "2.0"))
	float projectileSize = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE || (type == ESpellType::SCATTER && isHitscan == false)", EditConditionHides))
	bool useGravity;
	//Trail
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type ==	ESpellType::PROJECTILE", EditConditionHides))
	bool hasTrail;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE && hasTrail == true", EditConditionHides))
	TObjectPtr<UEffectData> trailEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE && hasTrail == true", EditConditionHides))
	float trailLifetime;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE && hasTrail == true", EditConditionHides))
	bool trailPullEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE && hasTrail == true", EditConditionHides))
	float trailSize;
	//Penetrate
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == ESpellType::PROJECTILE || (type == ESpellType::SCATTER && isHitscan == false)", EditConditionHides))
	bool canPenetrate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "(type == ESpellType::PROJECTILE || (type == ESpellType::SCATTER && isHitscan == false)) && canPenetrate == true", EditConditionHides))
	int penetrateLimit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "(type == ESpellType::PROJECTILE || (type == ESpellType::SCATTER && isHitscan == false)) && canPenetrate == true", EditConditionHides))
	int damageLossPerHit;

	//AOE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isAOE;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "isAOE == true", EditConditionHides))
	float aoeRange = 0.0f;
	//Knockback
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != ESpellType::SELF", EditConditionHides))
	bool applyKnockback;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != ESpellType::SELF && applyKnockback == true", EditConditionHides))
	float knockbackStrength = 0.0f;
	//Caster Effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool applyCasterEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "applyCasterEffect == true", EditConditionHides))
	TObjectPtr<UEffectData> casterEffect;
	//AOE Effect
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool spawnAOEEffect = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "spawnAOEEffect == true", EditConditionHides))
	TObjectPtr<UEffectData> aoeEffect;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "spawnAOEEffect == true", EditConditionHides))
	float aoeEffectDuration;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "spawnAOEEffect == true", EditConditionHides))
	float aoeEffectSize;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "spawnAOEEffect == true", EditConditionHides))
	bool doPullEffect;
};
