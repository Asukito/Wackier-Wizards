// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellFactory.h"
#include "SpellIncludes.h"

ISpell* USpellFactory::CreateSpell(USpellData* spellData, ISpellCaster* owner)
{
	TScriptInterface<ISpell> spell = nullptr;
	TObjectPtr<USpellBase> spellBase = NewObject<USpellBase>();
	spellBase->Init(spellData, owner);

	switch (spellData->type)
	{
		case SpellType::PROJECTILE:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = UProjectileSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case SpellType::HITSCAN:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = UHitscanSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case SpellType::SELF:
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));
			spell = USelfSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
	}

	if (spell == nullptr)
	{
		return nullptr;
	}

	TScriptInterface<ISpell> toReturn = spell;

	if (spellData->isAOE == true)
	{
		spell = UAOESpellDecorator::Builder(toReturn.GetInterface()).Build()->_getUObject();
		toReturn = spell;
	}
	if (spellData->type == SpellType::PROJECTILE && spellData->hasTrail == true)
	{
		spell = UTrailSpellDecorator::Builder(toReturn.GetInterface()).Build()->_getUObject();
		toReturn = spell;
	}

	return toReturn.GetInterface();
}


