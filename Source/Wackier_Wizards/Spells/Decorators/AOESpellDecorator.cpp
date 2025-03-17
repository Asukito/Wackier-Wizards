// Fill out your copyright notice in the Description page of Project Settings.


#include "AOESpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../../Spells/SpellData.h"
#include "../SpellBase.h"
#include "Wackier_Wizards/Definitions.h"

//Generates a SphereOverlap at the collision location. The lower level ProcessHit function is then called on the actors within the overlap.
void UAOESpellDecorator::ProcessHit(AActor* hit, FVector location, int damageAdjustment)
{
	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECC_DamageableObject));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<TObjectPtr<AActor>> ignore;
	if (spellData->type == ESpellType::SELF)
	{
		ignore.Add(owner);
	}

	TArray<AActor*> targets;

	DrawDebugSphere(owner->GetWorld(), location, spellData->aoeRange, 12, FColor::Red, false, 1.0f);

	if (UKismetSystemLibrary::SphereOverlapActors(owner->GetWorld(), location, spellData->aoeRange, types, NULL, ignore, targets))
	{
		for (TObjectPtr<AActor> a : targets)
		{
			spell->ProcessHit(a, location, damageAdjustment);
		}
	}
}
