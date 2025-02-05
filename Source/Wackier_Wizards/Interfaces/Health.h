// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Health.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealth : public UInterface
{
	GENERATED_BODY()
};

class UHealthComponent;

class WACKIER_WIZARDS_API IHealth
{
	GENERATED_BODY()

public:
	virtual void Heal(int amount) {};
	virtual const int GetHealth(bool getPercent) noexcept { return 0; };
	virtual void Respawn() {};
};
