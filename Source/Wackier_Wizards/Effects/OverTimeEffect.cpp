// Fill out your copyright notice in the Description page of Project Settings.


#include "OverTimeEffect.h"
#include "EffectData.h"

void UOverTimeEffect::StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list)
{
	UBaseEffect::StartEffect(data, actor, list);

	duration = effectData->duration;
	_strength = effectData->strength;
}

void UOverTimeEffect::Update(float deltaTime)
{
	UBaseEffect::Update(deltaTime);

	if (hasEnded == true)
	{
		return;
	}

	_tickTimer += deltaTime;


	if (timer >= duration)
	{
		EndEffect();
		return;
	}

	if (_tickTimer >= 1.0f)
	{
		if (ProcessEffect() == false)
		{
			EndEffect();
		}

		_tickTimer = 0.0f;
	}
}
