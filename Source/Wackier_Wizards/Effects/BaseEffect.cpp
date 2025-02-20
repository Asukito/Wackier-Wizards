// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffect.h"
#include "../Components/EffectsComponent.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Damageable.h"
#include "../Interfaces/Health.h"
#include "EffectDoes.h"
#include "BounceEffectBonus.h"
#include "AOEEffectBonus.h"

void UBaseEffect::StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list)
{
	hasEnded = false;
	//Bind the EffectsComponent QueueRemoval function to clearDelegate;
	_clearDelegate.BindUObject(list, &UEffectsComponent::QueueRemoval);

	//Checks that the target is effectable and contains a reference if true. If not, clear the effect.
	if (IEffectable* Owner = Cast<IEffectable>(actor))
	{
		owner = Owner->_getUObject();
	}
	else
	{
		ClearEffect();
		return;
	}

	effectData = data;

	if (effectData->bonus == EffectBonusType::NONE)
	{
		return;
	}

	//Create and execute any bonus effects if necessary.
	UBaseEffectBonus* effect;

	switch (effectData->bonus)
	{
		case EffectBonusType::BOUNCE:
			effect = NewObject<UBounceEffectBonus>();
			effect->Init(data, actor, true);

			break;
		case EffectBonusType::AOE:
			effect = NewObject<UAOEEffectBonus>();
			effect->Init(data, actor, true);

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
				return !target->TakeDamage(effectData->strength, effectData->name);
			}

			break;
		case EffectDoes::DAMAGE_PERCENT:
			if (IHealth* target = owner->GetHealthAccess())
			{
				if (IDamageable* damageable = owner->GetDamageableAccess())
				{
					float maxHealth = target->GetMaxHealth();
					float amount =  FMath::RoundToFloat(((maxHealth * ((float)(effectData->strength) / 100))));

					return !damageable->TakeDamage(amount, effectData->name);;
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

		case EffectDoes::INC_SPEED:

			if (owner->HasMovementComponent() == true)
			{
				owner->AdjustWalkSpeed(effectData->strength);
				return true;
			}

			break;

		case EffectDoes::DEC_SPEED:

			if (owner->HasMovementComponent() == true)
			{
				owner->AdjustWalkSpeed(-(effectData->strength));
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

	case EffectDoes::INC_SPEED:

		if (owner->HasMovementComponent() == false)
		{
			return;
		}

		owner->AdjustWalkSpeed(-(effectData->strength));
		break;

	case EffectDoes::DEC_SPEED:

		if (owner->HasMovementComponent() == false)
		{
			return;
		}

		owner->AdjustWalkSpeed(effectData->strength);
		break;
	}
}

