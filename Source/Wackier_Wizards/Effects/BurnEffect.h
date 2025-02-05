// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffect.h"
#include "BurnEffect.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UBurnEffect : public UBaseEffect
{
	GENERATED_BODY()

public:
	void StartEffect(AActor* actor, UEffectsComponent* list) override;
	void Update(float deltaTime) override;

private:
	float _tickTimer;
	int _tickDamage;
};
