// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffect.h"
#include "../Components/EffectsComponent.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Damageable.h"
#include "../Interfaces/Health.h"
#include "EffectDoes.h"
#include "BounceEffectBonus.h"

void UBaseEffect::StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list)
{
	hasEnded = false;
	_clearDelegate.BindUObject(list, &UEffectsComponent::QueueRemoval);

	if (IEffectable* Owner = Cast<IEffectable>(actor))
	{
		owner = Owner;
	}
	else
	{
		ClearEffect();
	}

	effectData = data;

	if (effectData->bonus == EffectBonusType::NONE)
	{
		return;
	}

	switch (effectData->bonus)
	{
		case EffectBonusType::BOUNCE:
			UBounceEffectBonus* effect = NewObject<UBounceEffectBonus>();
			effect->Init(data, actor);

			break;
	}
}

void UBaseEffect::Update(float deltaTime)
{
	if (hasEnded == true)
	{
		return;
	}

	timer += deltaTime;
}

void UBaseEffect::EndEffect()
{
	hasEnded = true;
	ClearEffect();
}

void UBaseEffect::ClearEffect()
{
	_clearDelegate.ExecuteIfBound(this);
}

FString UBaseEffect::GetEffectName()
{
	return effectData->name;
}

bool UBaseEffect::ProcessEffect()
{
	switch (effectData->does)
	{
		case EffectDoes::DAMAGE:
			if (IDamageable* target = owner->GetDamageableAccess())
			{
				target->TakeDamage(effectData->strength, effectData->name);
				return true;
			}

			break;
		case EffectDoes::DAMAGE_PERCENT:
			if (IHealth* target = owner->GetHealthAccess())
			{
				if (IDamageable* damageable = owner->GetDamageableAccess())
				{
					float maxHealth = target->GetMaxHealth();
					float amount =  FMath::RoundToFloat(((maxHealth * ((float)(effectData->strength) / 100))));
					damageable->TakeDamage(amount, effectData->name);
					return true;
				}
			}

			break;
		case EffectDoes::HEAL:
			if (IHealth* target = owner->GetHealthAccess())
			{
				target->Heal(effectData->strength);
				return true;
			}

			break;

		case EffectDoes::HEAL_PERCENT:

			if (IHealth* target = owner->GetHealthAccess())
			{
				target->Heal(target->GetMaxHealth() * (effectData->strength / 100));
				return true;
			}

			break;

		case EffectDoes::INC_MAXHP:

			if (IHealth* target = owner->GetHealthAccess())
			{
				target->AdjustMaxHealth(effectData->strength);
				return true;
			}

			break;
		case EffectDoes::DEC_MAXHP:

			if (IHealth* target = owner->GetHealthAccess())
			{
				target->AdjustMaxHealth(-(effectData->strength));
				return true;
			}

			break;
	}

	return false;
}

void UBaseEffect::ProcessEffectRemoval()
{
	switch (effectData->does)
	{
	case EffectDoes::INC_MAXHP:

		if (IHealth* target = owner->GetHealthAccess())
		{
			target->AdjustMaxHealth(-(effectData->strength));
		}

		break;
	case EffectDoes::DEC_MAXHP:

		if (IHealth* target = owner->GetHealthAccess())
		{
			target->AdjustMaxHealth(effectData->strength);
		}

		break;
	}
}

