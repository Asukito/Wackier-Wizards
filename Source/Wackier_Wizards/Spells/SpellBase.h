// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellBase.generated.h"

class USpellData;
class ISpellCaster;

UCLASS()
class WACKIER_WIZARDS_API USpellBase : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(USpellData* data, ISpellCaster* owner);
	virtual void CastSpell();

	void Empty();

protected:
	TWeakObjectPtr<USpellData> spellData;
	ISpellCaster* spellOwner;
};
