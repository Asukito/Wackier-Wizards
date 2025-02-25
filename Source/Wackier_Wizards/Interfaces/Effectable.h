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

class UAuraEffect;

class WACKIER_WIZARDS_API IEffectable
{
	GENERATED_BODY()

//Actors that implement the IEffectable interface can have effects applied to them. This also provides easier access to related interfaces to reduce casting. 
//This additional access logic (to the movement component as well) will ideally be moved.
public:
	virtual void AddEffect(UEffectData* effect) {};
	virtual IDamageable* GetDamageableAccess() { return nullptr; };
	virtual IHealth* GetHealthAccess() { return nullptr; };
	virtual UAuraEffect* GetAura() { return nullptr; };
	virtual bool HasMovementComponent() { return false; };
	virtual void AdjustWalkSpeed(float percent) {};
	virtual bool HasEffect(FString effectName) { return false; };
};
