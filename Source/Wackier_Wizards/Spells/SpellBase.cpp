// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"
#include "SpellData.h"
#include "../Effects/EffectData.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/SpellCaster.h"

void USpellBase::Init(USpellData* data, ISpellCaster* owner)
{
	spellData = data;
	spellOwner = owner->_getUObject();
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

	for (TObjectPtr<UEffectData> effect : effects)
	{
		int rand = FMath::RandRange(0, 100);

		if (rand <= spellData->effects[effect])
		{
			target->AddEffect(effect);
		}
	}

	effects.Empty();
}

void USpellBase::HandleInterfaceFunctions(AActor* actor)
{
	bool isKilled = false;

	if (IDamageable* target = Cast<IDamageable>(actor))
	{
		isKilled = target->TakeDamage(spellData->potency, spellData->name);
	}

	if (isKilled == true)
	{
		return;
	}

	if (IEffectable* effectable = Cast<IEffectable>(actor))
	{
		HandleEffects(effectable);
	}
}
