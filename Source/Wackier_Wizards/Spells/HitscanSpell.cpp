// Fill out your copyright notice in the Description page of Project Settings.

#include "HitscanSpell.h"
#include "SpellData.h"
#include "../Interfaces/SpellCaster.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UHitscanSpell::CastSpell()
{
	USpellBase::CastSpell();

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();
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

		HandleInterfaceFunctions(hit.GetActor());

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(owner->GetWorld(), spellData->collisionNiagara, hit.Location, FRotator::ZeroRotator);
	}
}
