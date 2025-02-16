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
	
	if (ownerSpell != nullptr)
	{
		ownerSpell->ProcessHit(owner, owner->GetActorLocation());
	}
	else
	{
		ProcessHit(owner, owner->GetActorLocation());
	}

	return true;
}

void USelfSpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	if (spellData->isAOE == true)
	{
		spell->ProcessHit(nullptr, location);
		return;
	}

	spell->ProcessHit(hit, location);
}

USpellBase* USelfSpellDecorator::GetBaseSpell()
{
	return nullptr;
}
