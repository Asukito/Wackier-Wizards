// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffect.h"
#include "OverTimeEffect.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UOverTimeEffect : public UBaseEffect
{
	GENERATED_BODY()
	
//An effect that repeats overtime
public:
	void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list) override;
	void Update(float deltaTime) override;

private:
	float _tickTimer;
	int _strength;
};
