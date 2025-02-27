// Fill out your copyright notice in the Description page of Project Settings.


#include "HitscanSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Spells/SpellData.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../SpellBase.h"

//Generates a linetrace using the spells parameters
bool UHitscanSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();
	FVector start = spellOwner->GetCastStartLocation();
	FVector end = ((spellOwner->GetCastStartForward() * spellData->range) + start);

	//Uncomment Niagara logic when proper Hitscan Niagara systems are created.
	//UNiagaraComponent* vfx = UNiagaraFunctionLibrary::SpawnSystemAtLocation(spellOwner->GetSpellOwner()->GetWorld(), spellData->spellNiagara, start, spellOwner->GetCastStartForward().Rotation());

	FVector hitEnd;
	FireLineTrace(owner, start, end, hitEnd);

	return true;
}

void UHitscanSpellDecorator::ProcessHit(AActor* hit, FVector location, int damageAdjustment)
{
	spell->ProcessHit(hit, location, damageAdjustment);
}

USpellBase* UHitscanSpellDecorator::GetBaseSpell()
{
	return Cast<USpellBase>(spell.GetObject());
}
