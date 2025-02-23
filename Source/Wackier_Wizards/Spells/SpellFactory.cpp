// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellFactory.h"
#include "SpellIncludes.h"

//Creates a SpellBase and then applies Decorators to it. Returns the result.
ISpell* USpellFactory::CreateSpell(USpellData* spellData, ISpellCaster* owner)
{
	TScriptInterface<ISpell> spell = nullptr;
	//Creates and initialises a SpellBase object.
	TObjectPtr<USpellBase> spellBase = NewObject<USpellBase>();
	spellBase->Init(spellData, owner);

	//Applies a SpellType Decorator to the SpellBase. This is the lowest level Decorator.
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
		case SpellType::SCATTER:
			spell = UScatterSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
	}

	if (spell == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("FAILED TO CREATE SPELL")));
		return nullptr;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));

	//Applies any additional Decorators to the spell if necessary.
	if (spellData->isAOE == true)
	{
		spell = UAOESpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}
	if (spellData->type == SpellType::PROJECTILE && spellData->hasTrail == true)
	{
		spell = UTrailSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}
	if (spellData->type != SpellType::SELF && spellData->applyKnockback == true)
	{
		spell = UKnockbackSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}
	if (spellData->applyCasterEffect == true)
	{
		spell = UCasterEffectSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}
	if (spellData->spawnAOEEffect == true)
	{
		spell = UAOEEffectSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}

	return spell.GetInterface();
}


