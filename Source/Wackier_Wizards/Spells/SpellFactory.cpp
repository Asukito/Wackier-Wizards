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
			spell = UProjectileSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case SpellType::HITSCAN:
			spell = UHitscanSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case SpellType::BEAM:
			spell = UBeamSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case SpellType::SELF:
			spell = USelfSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
	}

	if (spell == nullptr)
	{
		return nullptr;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));

	TScriptInterface<ISpell> toReturn = spell;


	if (spellData->isAOE == true)
	{
		toReturn = UAOESpellDecorator::Builder(toReturn.GetInterface()).Build()->_getUObject();
	}
	if (spellData->type == SpellType::PROJECTILE && spellData->hasTrail == true)
	{
		toReturn = UTrailSpellDecorator::Builder(toReturn.GetInterface()).Build()->_getUObject();
	}
	if (spellData->type != SpellType::SELF && spellData->applyKnockback == true)
	{
		toReturn = UKnockbackSpellDecorator::Builder(toReturn.GetInterface()).Build()->_getUObject();
	}

	return toReturn.GetInterface();
}


