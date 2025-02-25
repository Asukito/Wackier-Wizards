// Fill out your copyright notice in the Description page of Project Settings.


#include "PenetrateSpellDecorator.h"
#include "../SpellBase.h"
#include "../../Objects/Projectile.h"
#include "../SpellData.h"

void UPenetrateSpellDecorator::FireProjectile(FVector direction)
{
	spell->FireProjectile(direction);
	GetBaseSpell()->GetProjectile()->InitPenetrate();
}
