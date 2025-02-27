// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEffectBonus.generated.h"

class UEffectData;

UCLASS()
class WACKIER_WIZARDS_API UBaseEffectBonus : public UObject
{
	GENERATED_BODY()
	
//Base class for EffectBonuses.
public:
	void Init(UEffectData* data, AActor* owner, bool createCopy);

protected:
	virtual void DoBonus();

protected:
	TObjectPtr<AActor> effectOwner;
	TObjectPtr<UEffectData> effectData;
};
