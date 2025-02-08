// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffect.h"
#include "InstantEffect.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UInstantEffect : public UBaseEffect
{
	GENERATED_BODY()
	
public:
	void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list) override;
};
