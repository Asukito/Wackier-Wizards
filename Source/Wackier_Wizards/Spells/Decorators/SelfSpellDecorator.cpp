// Fill out your copyright notice in the Description page of Project Settings.


#include "SelfSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Spells/SpellData.h"

bool USelfSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();
	
	if (spellData->isAOE == true)
	{
		GetDecorator()->ProcessHit(nullptr, owner->GetActorLocation());
	}
	else
	{
		GetDecorator()->ProcessHit(owner, owner->GetActorLocation());
	}

	return true;
}

