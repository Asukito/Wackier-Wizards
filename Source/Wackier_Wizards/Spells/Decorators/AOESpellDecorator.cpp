// Fill out your copyright notice in the Description page of Project Settings.


#include "AOESpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Spells/SpellData.h"
#include "../SpellBase.h"

bool UAOESpellDecorator::CastSpell()
{
	return spell->CastSpell();
}

void UAOESpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<TObjectPtr<AActor>> ignore;
	if (spellData->type == SpellType::SELF)
	{
		ignore.Add(owner);
	}

	TArray<AActor*> targets;

	DrawDebugSphere(owner->GetWorld(), location, spellData->aoeRange, 12, FColor::Red, false, 1.0f);

	if (UKismetSystemLibrary::SphereOverlapActors(owner->GetWorld(), location, spellData->aoeRange, types, NULL, ignore, targets))
	{
		for (TObjectPtr<AActor> a : targets)
		{
			spell->ProcessHit(a, location);
		}
	}
}
