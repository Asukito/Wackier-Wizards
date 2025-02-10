// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../Effects/EffectData.h"
#include "../Interfaces/Damageable.h"
#include "../Interfaces/Health.h"
#include "Effectable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEffectable : public UInterface
{
	GENERATED_BODY()
};

class WACKIER_WIZARDS_API IEffectable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AddEffect(UEffectData* effect) {};
	virtual IDamageable* GetDamageableAccess() { return nullptr; };
	virtual IHealth* GetHealthAccess() { return nullptr; };
	virtual bool HasEffect(FString effectName) { return false; };
};
