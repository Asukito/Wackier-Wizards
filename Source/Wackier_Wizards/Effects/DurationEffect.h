// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffect.h"
#include "DurationEffect.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UDurationEffect : public UBaseEffect
{
	GENERATED_BODY()

//An effect that persists for a set amount of time. The effect is then reversed at the end of the time.
public:
	virtual void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list);
	virtual void Update(float deltaTime);
	virtual void EndEffect();
};
