// Fill out your copyright notice in the Description page of Project Settings.


#include "BurnEffect.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Damageable.h"

void UBurnEffect::StartEffect(AActor* actor, UEffectsComponent* list)
{
	UBaseEffect::StartEffect(actor, list);

	duration = 10.0f;
	_tickDamage = 3.0f;
}

void UBurnEffect::Update(float deltaTime)
{
	UBaseEffect::Update(deltaTime);
	_tickTimer += deltaTime;

	if (timer >= duration)
	{
		EndEffect();
		return;
	}

	if (_tickTimer >= 1.0f)
	{
		if (IDamageable* target = owner->GetDamageableAccess())
		{
			target->TakeDamage(_tickDamage, "Burn");
		}

		_tickTimer = 0.0f;
	}

}
