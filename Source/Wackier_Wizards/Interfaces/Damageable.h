// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Damageable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UDamageable : public UInterface
{
	GENERATED_BODY()
};

class WACKIER_WIZARDS_API IDamageable
{
	GENERATED_BODY()

//Actors the implement the IDamageable interface can take damage. This is separate from IHealth so actors that don't need health can take damage. 
//Examples would be the PracticeDummy and destructible actors (these can also have a health value).
public:
	virtual bool TakeDamage(int amount, FString source) { return true; };
	virtual void Kill() {};
};
