// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellFactory.generated.h"

class USpellBase;
class USpellData;
class ISpellCaster;

UCLASS()
class WACKIER_WIZARDS_API USpellFactory : public UObject
{
	GENERATED_BODY()

public:
	USpellBase* CreateSpell(USpellData* spellData, ISpellCaster* owner);
};
