// Fill out your copyright notice in the Description page of Project Settings.

#include "SelfSpell.h"
#include "SpellData.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/SpellCaster.h"
#include "NiagaraFunctionLibrary.h"

void USelfSpell::CastSpell()
{
	USpellBase::CastSpell();

	AActor* owner = spellOwner->GetSpellOwner();

	if (IHealth* healable = Cast<IHealth>(owner))
	{
		healable->Heal(spellData->potency);
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(owner->GetWorld(), spellData->spellNiagara, owner->GetActorLocation(), FRotator::ZeroRotator);
}
