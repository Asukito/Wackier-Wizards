// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"
#include "SpellData.h"
#include "../Effects/EffectData.h"
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
	if (spellData->effects.Num() == 0)
	{
		return;
	}

	TArray<TObjectPtr<UEffectData>> effects;
	spellData->effects.GenerateKeyArray(effects);

	for (UEffectData* effect : effects)
	{
		int rand = FMath::RandRange(0, 100);

		if (rand <= spellData->effects[effect])
		{
			target->AddEffect(effect);
		}
	}
}
