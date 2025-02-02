// Fill out your copyright notice in the Description page of Project Settings.

#include "SelfSpell.h"
#include "SpellData.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/SpellCaster.h"

void USelfSpell::CastSpell()
{
	USpellBase::CastSpell();

	if (IHealth* healable = Cast<IHealth>(spellOwner->GetSpellOwner()))
	{
		healable->Heal(spellData->potency);
	}
}
