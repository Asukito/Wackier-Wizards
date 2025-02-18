// Fill out your copyright notice in the Description page of Project Settings.


#include "CasterEffectSpellDecorator.h"
#include "../../Interfaces/Effectable.h"
#include "../../Interfaces/SpellCaster.h"
#include "../SpellData.h"

bool UCasterEffectSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	if (IEffectable* target = Cast<IEffectable>(spellOwner->GetSpellOwner()))
	{
		target->AddEffect(spellData->casterEffect);
	}

	return true;
}
