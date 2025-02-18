// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"
#include "SpellData.h"
#include "../Effects/EffectData.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/SpellCaster.h"
#include "NiagaraFunctionLibrary.h"

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

void USpellBase::ProcessHit(AActor* hit, FVector location)
{
	if (spellData->type != SpellType::SELF)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(spellOwner->GetSpellOwner()->GetWorld(), spellData->collisionNiagara, location, FRotator::ZeroRotator);
	}
	else
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(spellOwner->GetSpellOwner()->GetWorld(), spellData->spellNiagara, location, FRotator::ZeroRotator);
	}

	if (hit != nullptr)
	{
		HandleInterfaceFunctions(hit);
	}
}

void USpellBase::SetOwnerSpell(ISpell* owner)
{
	ownerSpell = owner->_getUObject();
}

void USpellBase::Update(float deltaTime)
{
	if (_cooldownTimer < 0)
	{
		return;
	}

	_cooldownTimer -= deltaTime;
}

USpellBase* USpellBase::GetBaseSpell()
{
	return this;
}

const FString USpellBase::GetSpellName()
{
	return spellData->name;
}

const float USpellBase::GetSpellRange()
{
	return spellData->range;
}

USpellData* USpellBase::GetSpellData()
{
	return spellData.Get();
}

ISpellCaster* USpellBase::GetSpellOwner()
{
	return spellOwner.GetInterface();
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

	if (spellData->type != SpellType::SELF || (spellData->type == SpellType::SELF && actor != spellOwner->GetSpellOwner()))
	{
		if (IDamageable* target = Cast<IDamageable>(actor))
		{
			isKilled = target->TakeDamage(spellData->potency, spellData->name);
		}

		if (isKilled == true)
		{
			return;
		}
	}

	if (IEffectable* effectable = Cast<IEffectable>(actor))
	{
		HandleEffects(effectable);
	}
}

void USpellBase::SetProjectile(AProjectile* projectile)
{
	_projectile = projectile;
}

AProjectile* USpellBase::GetProjectile()
{
	return _projectile;
}
