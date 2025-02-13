// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AOEProjectileSpell.h"
#include "TrailAOEProjectileSpell.generated.h"


UCLASS()
class WACKIER_WIZARDS_API UTrailAOEProjectileSpell : public UAOEProjectileSpell
{
	GENERATED_BODY()
	
public:
	bool CastSpell() override;
};
