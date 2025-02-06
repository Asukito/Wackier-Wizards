// Fill out your copyright notice in the Description page of Project Settings.


#include "InstantEffect.h"
#include "EffectData.h"

void UInstantEffect::StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list)
{
	UBaseEffect::StartEffect(data, actor, list);

	ProcessEffect();
	ClearEffect();
}
