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

/**
 * 
 */
class WACKIER_WIZARDS_API IDamageable
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(int amount, FString source) {};
};
