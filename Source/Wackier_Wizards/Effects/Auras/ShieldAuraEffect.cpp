// Fill out your copyright notice in the Description page of Project Settings.


#include "ShieldAuraEffect.h"
#include "Components/SphereComponent.h"
#include "../../Objects/Projectile.h"
#include "../EffectData.h"

void UShieldAuraEffect::DamageShield(int amount, FString source)
{
	shieldVal -= amount;
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s: Taken %i damage from %s"), *GetName(), amount, *source));

	bool isDead = (shieldVal <= 0);

	if (isDead)
	{
		Kill();
	}
}

bool UShieldAuraEffect::DealDamage(int amount, FString source)
{
	return false;
}

void UShieldAuraEffect::Kill()
{
	EndEffect();
}

void UShieldAuraEffect::StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list)
{
	UAuraEffect::StartEffect(data, actor, list);

	shieldVal = effectData->strength;
}
