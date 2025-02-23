// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatterSpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Spells/SpellData.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "../SpellBase.h"

bool UScatterSpellDecorator::CastSpell()
{
	if (spell->CastSpell() == false)
	{
		return false;
	}

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();
	FVector start = spellOwner->GetCastStartLocation();

	float min = 1 - spellData->scatterRange;
	float max = 1 + spellData->scatterRange;

	FVector unitDirection = spellOwner->GetCastStartForward();
	unitDirection.Normalize();

	FVector hitEnd;

	for (int i = 0; i < spellData->scatterAmount; i++)
	{
		double dotX = FMath::RandRange(min, max) - 1;
		double dotZ = FMath::RandRange(min, max) - 1;

		FVector direction = unitDirection + FVector(dotX, 0, dotZ);

		if (spellData->isHitscan == true)
		{
			//Uncomment Niagara logic when proper Hitscan Niagara systems are created.
			//UNiagaraComponent* vfx = UNiagaraFunctionLibrary::SpawnSystemAtLocation(spellOwner->GetSpellOwner()->GetWorld(), spellData->spellNiagara, start, spellOwner->GetCastStartForward().Rotation());

			FVector end = ((direction * spellData->range) + start);
			FireLineTrace(owner, start, end , hitEnd);
		}
		else
		{
			FireProjectile(direction);
		}
	}

	return true;
}

void UScatterSpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	spell->ProcessHit(hit, location);
}

USpellBase* UScatterSpellDecorator::GetBaseSpell()
{
	return Cast<USpellBase>(spell.GetObject());;
}
