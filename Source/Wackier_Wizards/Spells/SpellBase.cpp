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
	_cooldown = spellData->cooldown;
	_cooldownTimer = 0.0f;
}

bool USpellBase::CastSpell()
{
	if (_cooldownTimer > 0.0f)
	{
		return false;
	}

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Green, FString::Printf(TEXT("Casting: %s"), *spellData->name));
	_cooldownTimer = _cooldown;

	return true;
}

void USpellBase::Update(float deltaTime)
{
	if (_cooldownTimer < 0)
	{
		return;
	}

	_cooldownTimer -= deltaTime;
}

const FString USpellBase::GetSpellName()
{
	return spellData->name;
}

bool USpellBase::IsOnCooldown()
{
	return (_cooldownTimer > 0.0f);
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
