// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellBase.h"
#include "AOEHitscanSpell.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UAOEHitscanSpell : public USpellBase
{
	GENERATED_BODY()

public:
	bool CastSpell() override;
};
