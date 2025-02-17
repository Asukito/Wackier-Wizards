// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailSpellDecorator.h"
#include "../SpellBase.h"
#include "../../Objects/Projectile.h"
#include "../SpellData.h"
bool UTrailSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	AProjectile* projectile = GetBaseSpell()->GetProjectile();
	projectile->InitTrail(spellData->trailEffect);

	return true;
}

USpellBase* UTrailSpellDecorator::GetBaseSpell()
{
	return spell->GetBaseSpell();
}

ISpell* UTrailSpellDecorator::GetOwnerSpell()
{
	if (ownerSpell == nullptr)
	{
		return nullptr;
	}

	return ownerSpell.GetInterface();
}

