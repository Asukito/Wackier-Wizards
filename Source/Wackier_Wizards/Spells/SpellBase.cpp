// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellBase.h"
#include "SpellData.h"
#include "../Effects/EffectData.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/SpellCaster.h"
#include "NiagaraFunctionLibrary.h"
#include "../Effects/Auras/ShieldAuraEffect.h"
#include "../Objects/Projectile.h"

void USpellBase::Init(USpellData* data, ISpellCaster* owner)
{
	spellData = data;
	spellOwner = owner->_getUObject();
	_cooldown = spellData->cooldown;
	_cooldownTimer = 0.0f;
}
//Checks if the spell can be cast. Currently only checks if the cooldown is active, will include mana cost in future.
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

//Spawns relevant Niagara to display a hit. In the case of SelfSpells, spawns the Niagara for the spell.
void USpellBase::ProcessHit(AActor* hit, FVector location, int damageAdjustment)
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
		HandleInterfaceFunctions(hit, damageAdjustment);
	}
}

void USpellBase::FireLineTrace(AActor* owner, FVector start, FVector end, FVector& OutEnd)
{
	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(owner);

	if (owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic, params))
	{
		DrawDebugLine(owner->GetWorld(), start, hit.Location, FColor::Green, false, 2.0f);

		GetDecorator()->ProcessHit(hit.GetActor(), hit.Location, 0);
	}
	else
	{
		DrawDebugLine(owner->GetWorld(), start, end, FColor::Green, false, 2.0f);
	}

	OutEnd = end;
}

void USpellBase::FireProjectile(FVector direction)
{
	TObjectPtr<AActor> owner = spellOwner->GetSpellOwner();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AProjectile* projectile = owner->GetWorld()->SpawnActor<AProjectile>(AProjectile::StaticClass(), spellOwner->GetCastStartLocation(), FRotator::ZeroRotator, spawnParams);
	projectile->AddIgnoreActor(owner);

	projectile->AddOwnerSpell(GetDecorator());

	projectile->InitNiagara(spellData->spellNiagara);
	projectile->SetRange(spellData->range);

	GetBaseSpell()->SetProjectile(projectile);

	projectile->SetIsActive(true);
	projectile->ApplyForce(spellData->useGravity, direction, spellData->speed);
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


//Handles any effects and applies them to the target
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

//Handles any Interface logic relevant to the hit actor. Including damage (IDamageable) and effects (IEffectable). Will include healing spells if the logic is needed outside of SelfSpells.
//Currently SelfSpells can apply heals by applying an effect that heals.
void USpellBase::HandleInterfaceFunctions(AActor* actor, int damageAdjustment)
{
	bool isKilled = false;
	IEffectable* effectable = Cast<IEffectable>(actor);

	if (spellData->type != SpellType::SELF || (spellData->type == SpellType::SELF && actor != spellOwner->GetSpellOwner()))
	{
		if (effectable != nullptr)
		{
			if (TObjectPtr<UShieldAuraEffect> shield = Cast<UShieldAuraEffect>(effectable->GetAura()))
			{
				shield->DamageShield(spellData->potency + damageAdjustment, spellData->name);
				return;
			}
		}

		if (IDamageable* target = Cast<IDamageable>(actor))
		{
			isKilled = target->DamageTake(spellData->potency + damageAdjustment, spellData->name);
		}

		if (isKilled == true)
		{
			return;
		}
	}

	if (effectable != nullptr)
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

#pragma region "Helpers"
USpellBase* USpellBase::GetBaseSpell()
{
	return this;
}

ISpell* USpellBase::GetDecorator()
{
	if (ownerSpell == nullptr)
	{
		return this;
	}

	return ownerSpell->GetDecorator();
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
int USpellBase::GetSpellDamage()
{
	return spellData->potency;
}
#pragma endregion