// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpellBase.generated.h"

class USpellData;
class ISpellCaster;
class IEffectable;

UCLASS()
class WACKIER_WIZARDS_API USpellBase : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(USpellData* data, ISpellCaster* owner);
	virtual void CastSpell();

protected:
	void HandleEffects(IEffectable* target);
	void HandleInterfaceFunctions(AActor* actor);

protected:
	UPROPERTY()
	TWeakObjectPtr<USpellData> spellData;
	UPROPERTY()
	TScriptInterface<ISpellCaster> spellOwner;
};
