// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCasterComponent.h"
#include "../Spells/SpellBase.h"
#include "../Spells/SpellData.h"
#include "../Spells/SpellFactory.h"
#include "../Interfaces/Spell.h"

USpellCasterComponent::USpellCasterComponent()
{	
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

//Creates the spells from the contained spellData and then sets the active sell to the first
void USpellCasterComponent::InitSpells()
{
	if (_spellData.Num() == 0)
	{
		return;
	}

	TObjectPtr<USpellFactory> factory = NewObject<USpellFactory>();

	for (USpellData* data : _spellData)
	{
		_spells.Add(factory->CreateSpell(data, this)->_getUObject());
	}
	
	ChangeSpell(1);
}

void USpellCasterComponent::CastSpell()
{
	if (_spell == nullptr)
	{
		return;
	}

	_spell->CastSpell();
}

void USpellCasterComponent::ChangeSpell(int slot)
{
	if (_spells.Num() == 0 || slot - 1 < 0 || slot > _spells.Num())
	{
		return;
	}

	_spell = _spells[slot - 1];
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, FString::Printf(TEXT("Current Spell: %s"), *_spell->GetSpellName()));
}

void USpellCasterComponent::CycleSpell()
{
	_currentSpellIndex += 1;

	if (_currentSpellIndex > _spells.Num())
	{
		_currentSpellIndex = 1;
	}

	ChangeSpell(_currentSpellIndex);
}

void USpellCasterComponent::BindCastStartLocation(TFunction<const FVector()> func)
{
	_castStartLocation.BindLambda(func);
}

void USpellCasterComponent::BindCastStartForward(TFunction<const FVector()> func)
{
	_castStartForward.BindLambda(func);
}

void USpellCasterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_spells.Num() == 0)
	{
		return;
	}

	for (TScriptInterface<ISpell> spell : _spells)
	{
		spell->Update(DeltaTime);
	}
}

AActor* USpellCasterComponent::GetSpellOwner() noexcept
{
	return GetOwner();
}

const FVector USpellCasterComponent::GetSpellOwnerLocation() noexcept
{
	return GetOwner()->GetActorLocation();
}

const FVector USpellCasterComponent::GetSpellOwnerForward() noexcept
{
	return GetOwner()->GetActorForwardVector();
}

const FVector USpellCasterComponent::GetCastStartLocation() noexcept
{
	//If castStartLocation isn't bound, return the spellOwner location. Else, execute the bound function.
	if (_castStartLocation.IsBound() == false)
	{
		return GetSpellOwnerLocation();
	}

	return _castStartLocation.Execute();
}

const FVector USpellCasterComponent::GetCastStartForward() noexcept
{
	//If castStartForward isn't bound, return the spellOwner forward. Else, execute the bound function.
	if (_castStartForward.IsBound() == false)
	{
		return GetSpellOwnerForward();
	}

	return _castStartForward.Execute();
}

ISpell* USpellCasterComponent::GetActiveSpell() noexcept
{
	return _spell.GetInterface();
}

