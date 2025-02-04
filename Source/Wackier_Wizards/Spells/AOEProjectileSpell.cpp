// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEProjectileSpell.h"
#include "../Interfaces/Damageable.h"
#include "../Interfaces/SpellCaster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SpellData.h"

void UAOEProjectileSpell::ProcessHit(AActor* actor, FVector projectileLocation)
{
	AActor* owner = spellOwner->GetSpellOwner();

	TArray<TEnumAsByte<EObjectTypeQuery>> types;
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> ignore;
	TArray<AActor*> targets;

	DrawDebugSphere(owner->GetWorld(), projectileLocation, spellData->aoeRange, 12, FColor::Red, false, 1.0f);
	if (UKismetSystemLibrary::SphereOverlapActors(owner->GetWorld(), projectileLocation, spellData->aoeRange, types, NULL, ignore, targets))
	{
		for (AActor* actor : targets)
		{
			if (IDamageable* hit = Cast<IDamageable>(actor))
			{
				hit->TakeDamage(spellData->potency, spellData->name);
			}
		}
	}
}
