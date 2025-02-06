// Fill out your copyright notice in the Description page of Project Settings.

#include "SelfSpell.h"
#include "SpellData.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/SpellCaster.h"
#include "NiagaraFunctionLibrary.h"

void USelfSpell::CastSpell()
{
	USpellBase::CastSpell();

	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	if (TScriptInterface<IEffectable> effectable = Cast<IEffectable>(owner)->_getUObject())
	{
		HandleEffects(effectable.GetInterface());
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(owner->GetWorld(), spellData->spellNiagara, owner->GetActorLocation(), FRotator::ZeroRotator);
}
