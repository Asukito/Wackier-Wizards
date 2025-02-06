// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBase.h"
#include "ProjectileSpell.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UProjectileSpell : public USpellBase
{
	GENERATED_BODY()
	
public:
	void CastSpell() override;
	virtual void ProcessHit(AActor* actor, FVector projectileLocation);
};
