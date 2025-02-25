// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatterSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Spells/SpellData.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../SpellBase.h"
#include "Kismet/KismetMathLibrary.h"

bool UScatterSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();
	FVector start = spellOwner->GetCastStartLocation();

	FVector unitDirection = spellOwner->GetCastStartForward();
	unitDirection.Normalize();

	FVector hitEnd;

	for (int i = 0; i < spellData->scatterAmount; i++)
	{
		FVector direction = unitDirection + (UKismetMathLibrary::RandomUnitVectorInConeInDegrees(unitDirection, spellData->scatterRange));

		if (spellData->isHitscan == true)
		{
			//Uncomment Niagara logic when proper Hitscan Niagara systems are created.
			//UNiagaraComponent* vfx = UNiagaraFunctionLibrary::SpawnSystemAtLocation(spellOwner->GetSpellOwner()->GetWorld(), spellData->spellNiagara, start, spellOwner->GetCastStartForward().Rotation());

			FVector end = ((direction * spellData->range) + start);
			GetDecorator()->FireLineTrace(owner, start, end, hitEnd);
		}
		else
		{
			GetDecorator()->FireProjectile(direction);
		}
	}

	return true;
}

void UScatterSpellDecorator::ProcessHit(AActor* hit, FVector location, int damageAdjustment)
{
	spell->ProcessHit(hit, location, damageAdjustment);
}

USpellBase* UScatterSpellDecorator::GetBaseSpell()
{
	return Cast<USpellBase>(spell.GetObject());;
}
