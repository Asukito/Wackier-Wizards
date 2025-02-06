// Fill out your copyright notice in the Description page of Project Settings.


#include "DurationEffect.h"
#include "EffectData.h"

void UDurationEffect::StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list)
{
	UBaseEffect::StartEffect(data, actor, list);

	if (ProcessEffect() == false)
	{
		ClearEffect();
	}

	duration = effectData->duration;
}

void UDurationEffect::Update(float deltaTime)
{
	UBaseEffect::Update(deltaTime);

	if (hasEnded == false && timer >= duration)
	{
		EndEffect();
	}
}

void UDurationEffect::EndEffect()
{
	ProcessEffectRemoval();
	UBaseEffect::EndEffect();
}
