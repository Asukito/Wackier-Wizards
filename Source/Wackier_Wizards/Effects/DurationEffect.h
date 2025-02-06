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
	
public:
	virtual void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list);
	virtual void Update(float deltaTime);
	virtual void EndEffect();
};
