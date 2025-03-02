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
		case ESpellType::PROJECTILE:
			spell = UProjectileSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case ESpellType::HITSCAN:
			spell = UHitscanSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case ESpellType::BEAM:
			spell = UBeamSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case ESpellType::SELF:
			spell = USelfSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
		case ESpellType::SCATTER:
			spell = UScatterSpellDecorator::Builder(spellBase).Build()->_getUObject();

			break;
	}

	if (spell == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("FAILED TO CREATE SPELL")));
		return nullptr;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Cyan, FString::Printf(TEXT("Created %s"), *spellData->name));

	//Applies any additional Decorators to the spell if necessary.

	//Decorators that modify the creation of a projectile
	if (spellData->type == ESpellType::PROJECTILE && spellData->hasTrail == true)
	{
		spell = UTrailSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}
	if ((spellData->type == ESpellType::PROJECTILE || (spellData->type == ESpellType::SCATTER && spellData->isHitscan == false)) && spellData->canPenetrate == true)
	{
		spell = UPenetrateSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}

	//OnHit Decorators. Anything wanted to be affected by AOE decorate beforehand (such as knockback). 
	if (spellData->type != ESpellType::SELF && spellData->applyKnockback == true)
	{
		spell = UKnockbackSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}
	if (spellData->isAOE == true)
	{
		spell = UAOESpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}
	if (spellData->spawnAOEEffect == true)
	{
		spell = UAOEEffectSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}

	//Decorators that apply to the caster
	if (spellData->applyCasterEffect == true)
	{
		spell = UCasterEffectSpellDecorator::Builder(spell.GetInterface()).Build()->_getUObject();
	}

	return spell.GetInterface();
}


