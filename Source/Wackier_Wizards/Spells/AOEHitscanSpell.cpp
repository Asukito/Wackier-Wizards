// Fill out your copyright notice in the Description page of Project Settings.


#include "AOEHitscanSpell.h"
#include "SpellData.h"
#include "../Interfaces/SpellCaster.h"
#include "../Interfaces/Damageable.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UAOEHitscanSpell::CastSpell()
{
	USpellBase::CastSpell();

	AActor* owner = spellOwner->GetSpellOwner();
	FVector start = spellOwner->GetCastStartLocation();
	FVector end = ((spellOwner->GetSpellOwnerForward() * spellData->range) + start);

	DrawDebugLine(owner->GetWorld(), start, end, FColor::Green, true);

	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(owner);

	if (owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_GameTraceChannel1, params))
	{
		if (hit.GetActor() == nullptr)
		{
			return;
		}

		TArray<TEnumAsByte<EObjectTypeQuery>> types;
		types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
		types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		types.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

		TArray<AActor*> ignore;
		TArray<AActor*> targets;

		DrawDebugSphere(owner->GetWorld(), hit.Location, spellData->aoeRange, 12, FColor::Red, false, 1.0f);
		if (UKismetSystemLibrary::SphereOverlapActors(owner->GetWorld(), hit.Location, spellData->aoeRange, types, NULL, ignore, targets))
		{
			for (AActor* actor : targets)
			{
				if (IDamageable* damage = Cast<IDamageable>(actor))
				{
					damage->TakeDamage(spellData->potency, spellData->name);
				}
			}
		}

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(owner->GetWorld(), spellData->collisionNiagara, hit.Location, FRotator::ZeroRotator);
	}

	//cooldown timer = cooldown
}