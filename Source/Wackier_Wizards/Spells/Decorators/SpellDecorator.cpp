// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"
#include "../SpellData.h"
#include "../SpellBase.h"

void USpellDecorator::Decorate(ISpell* decorate)
{
	if (decorate == nullptr)
	{
		return;
	}

	spell = decorate->_getUObject();
	spellData = spell->GetSpellData();
	spellOwner = spell->GetSpellOwner()->_getUObject();
}

void USpellDecorator::SetOwnerSpell(ISpell* owner)
{
	ownerSpell = owner->_getUObject();
}

bool USpellDecorator::CastSpell()
{
	return spell->CastSpell();
}

void USpellDecorator::Update(float deltaTime)
{
	spell->Update(deltaTime);
}

void USpellDecorator::ProcessHit(AActor* hit, FVector location, int damageAdjustment)
{
	spell->ProcessHit(hit, location, damageAdjustment);
}

const FString USpellDecorator::GetSpellName()
{
	return spell->GetSpellName();
}

const float USpellDecorator::GetSpellRange()
{
	return spell->GetSpellRange();
}

USpellData* USpellDecorator::GetSpellData()
{
	return spell->GetSpellData();
}

ISpellCaster* USpellDecorator::GetSpellOwner()
{
	return spell->GetSpellOwner();
}

USpellBase* USpellDecorator::GetBaseSpell()
{
	if (spell == nullptr)
	{
		return nullptr;
	}

	return spell->GetBaseSpell();
}

ISpell* USpellDecorator::GetDecorator()
{
	if (ownerSpell == nullptr)
	{
		return this;
	}

	return ownerSpell->GetDecorator();
}

void USpellDecorator::FireLineTrace(AActor* owner, FVector start, FVector end, FVector& OutEnd)
{
	spell->FireLineTrace(owner, start, end, OutEnd);
}

void USpellDecorator::FireProjectile(FVector direction)
{
	spell->FireProjectile(direction);
}

bool USpellDecorator::IsOnCooldown()
{
	return spell->IsOnCooldown();
}

int USpellDecorator::GetSpellDamage()
{
	return spell->GetSpellDamage();
}