// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectBonus.h"
#include "BounceEffectBonus.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UBounceEffectBonus : public UBaseEffectBonus
{
	GENERATED_BODY()

//Bonus effect that allows the effect to bounce to nearby targets
protected:
	virtual void DoBonus() override;
};
