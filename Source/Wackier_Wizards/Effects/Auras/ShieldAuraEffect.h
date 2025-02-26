// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraEffect.h"
#include "../../Interfaces/Damageable.h"
#include "ShieldAuraEffect.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UShieldAuraEffect : public UAuraEffect, public IDamageable
{
	GENERATED_BODY()
	
public:
	void DamageShield(int amount, FString source);

	virtual bool DealDamage(int amount, FString source) final;
	virtual void Kill() final;

	virtual void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list) override;

private:
	float shieldVal;
};
