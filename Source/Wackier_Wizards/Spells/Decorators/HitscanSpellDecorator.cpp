// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Spells/SpellData.h"

bool UHitscanSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();
	FVector start = spellOwner->GetCastStartLocation();
	FVector end = ((spellOwner->GetCastStartForward() * spellData->range) + start);

	DrawDebugLine(owner->GetWorld(), start, end, FColor::Green, false, 2.0f);

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(owner);

	if (owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic, params))
	{
		if (ownerSpell != nullptr)
		{
			ownerSpell->ProcessHit(hit.GetActor(), hit.Location);
		}
		else
		{
			ProcessHit(hit.GetActor(), hit.Location);
		}
	}

	return true;
}

void UHitscanSpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	spell->ProcessHit(hit, location);
}

USpellBase* UHitscanSpellDecorator::GetBaseSpell()
{
	return spell->GetBaseSpell();
}
