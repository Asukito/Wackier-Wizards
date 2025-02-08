// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectBonus.h"
#include "AOEEffectBonus.generated.h"

class AAOEActor;

UCLASS()
class WACKIER_WIZARDS_API UAOEEffectBonus : public UBaseEffectBonus
{
	GENERATED_BODY()
	
public:
	virtual void DoBonus() override;
};
