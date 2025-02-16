// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellDecorator.h"
#include "../../Interfaces/SpellCaster.h"

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

void USpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	spell->ProcessHit(hit, location);
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

bool USpellDecorator::IsOnCooldown()
{
	return spell->IsOnCooldown();
}

void USpellDecorator::HandleEffects(IEffectable* target)
{
	spell->HandleEffects(target);
}

void USpellDecorator::HandleInterfaceFunctions(AActor* actor)
{
	spell->HandleInterfaceFunctions(actor);
}
