// Fill out your copyright notice in the Description page of Project Settings.


#include "TrailSpellDecorator.h"
#include "../SpellBase.h"
#include "../../Objects/Projectile.h"
#include "../SpellData.h"

//Inits Trail logic
void UTrailSpellDecorator::FireProjectile(FVector direction)
{
	spell->FireProjectile(direction);
	GetBaseSpell()->GetProjectile()->InitTrail();
}
