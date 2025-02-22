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

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(owner);
	
	if (owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic, params))
	{
		DrawDebugLine(owner->GetWorld(), start, hit.Location, FColor::Green, false, 2.0f);
		//vfx->SetVariableVec3(FName("TraceEnd"), hit.Location);

		GetDecorator()->ProcessHit(hit.GetActor(), hit.Location);
	}
	else
	{
		//vfx->SetVectorParameter(FName("TraceEnd"), end);
		DrawDebugLine(owner->GetWorld(), start, end, FColor::Green, false, 2.0f);
	}

	return true;
}

void UHitscanSpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	spell->ProcessHit(hit, location);
}

USpellBase* UHitscanSpellDecorator::GetBaseSpell()
{
	return Cast<USpellBase>(spell.GetObject());
}
