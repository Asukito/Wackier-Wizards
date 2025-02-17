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
	SpellType type = SpellType::HITSCAN;
	//AOE
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool isAOE;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "isAOE == true", EditConditionHides))
	float aoeRange = 0.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "isAOE == true", EditConditionHides))
	int aoeDamage = 0.0f;

	///---- NON-BEAM ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != SpellType::BEAM", EditConditionHides))
	float cooldown = 0.0f;

	//---- NON-SELF ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != SpellType::SELF", EditConditionHides))
	int potency = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != SpellType::SELF", EditConditionHides))
	float range = 0.0f;;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != SpellType::SELF", EditConditionHides))
	TObjectPtr<UNiagaraSystem> collisionNiagara;
	//Knockback
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type != SpellType::SELF", EditConditionHides))
	bool applyKnockback;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "applyKnockback == true", EditConditionHides))
	float knockbackStrength = 0.0f;

	//---- PROJECTILE ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE", EditConditionHides))
	float speed;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type == SpellType::PROJECTILE", EditConditionHides))
	bool useGravity;
	//Trail
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "type ==	SpellType::PROJECTILE", EditConditionHides))
	bool hasTrail;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (EditCondition = "hasTrail == true", EditConditionHides))
	TObjectPtr<UEffectData> trailEffect;
};
