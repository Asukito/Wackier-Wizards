// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpell.h"
#include "AOEProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UAOEProjectileSpell : public UProjectileSpell
{
	GENERATED_BODY()

public:

	void ProcessHit(AActor* actor, FVector projectileLocation) override;
};
