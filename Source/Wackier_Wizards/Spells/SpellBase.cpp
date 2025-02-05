// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"
#include "SpellData.h"
#include "../Effects/Effect.h"
#include "../Interfaces/Damageable.h"

void USpellBase::Init(USpellData* data, ISpellCaster* owner)
{
	spellData = data;
	spellOwner = owner;	
}

void USpellBase::CastSpell()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Casting: %s"), *spellData->name));
}

void USpellBase::HandleEffects(IEffectable* target)
{
	for (Effect effect : spellData->effects)
	{
		target->AddEffect(effect);
	}
}
