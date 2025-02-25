// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"

//Spawns and initialises a projectile
bool UProjectileSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	FVector unitDirection = spellOwner->GetCastStartForward();
	unitDirection.Normalize();

	GetDecorator()->FireProjectile(unitDirection);

	return true;
}

void UProjectileSpellDecorator::ProcessHit(AActor* hit, FVector location, int damageAdjustment)
{
	spell->ProcessHit(hit, location, damageAdjustment);
}
