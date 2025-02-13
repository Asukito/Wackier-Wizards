// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellCasterCharacter.h"
#include "../Spells/SpellBase.h"
#include "../Spells/SpellData.h"
#include "../Spells/SpellFactory.h"

ASpellCasterCharacter::ASpellCasterCharacter() : ABaseCharacter()
{
}

void ASpellCasterCharacter::InitSpells()
{
	if (_spellData.Num() == 0)
	{
		return;
	}

	TObjectPtr<USpellFactory> factory = NewObject<USpellFactory>();

	for (USpellData* data : _spellData)
	{
		_spells.Add(factory->CreateSpell(data, this));
	}

	factory->MarkAsGarbage();
}

void ASpellCasterCharacter::CastSpell()
{
	if (_spell == nullptr)
	{
		return;
	}

	_spell->CastSpell();
}

void ASpellCasterCharacter::ChangeSpell(int slot)
{
	if (_spells.Num() == 0 || slot - 1 < 0 || slot > _spells.Num())
	{
		return;
	}

	_spell = _spells[slot - 1];
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Magenta, FString::Printf(TEXT("Current Spell: %s"), *_spell->GetSpellName()));
}

void ASpellCasterCharacter::CycleSpell()
{
	_currentSpellIndex += 1;

	if (_currentSpellIndex > _spells.Num())
	{
		_currentSpellIndex = 1;
	}

	ChangeSpell(_currentSpellIndex);
}

void ASpellCasterCharacter::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	InitSpells();
}

void ASpellCasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_spells.Num() == 0)
	{
		return;
	}

	for (USpellBase* spell : _spells)
	{
		spell->Update(DeltaTime);
	}
}

AActor* ASpellCasterCharacter::GetSpellOwner() noexcept
{
	return this;
}

const FVector ASpellCasterCharacter::GetSpellOwnerLocation() noexcept
{
	return GetActorLocation();
}

const FVector ASpellCasterCharacter::GetSpellOwnerForward() noexcept
{
	return GetActorForwardVector();
}

const FVector ASpellCasterCharacter::GetCastStartLocation() noexcept
{
	return GetActorLocation();
}

const FVector ASpellCasterCharacter::GetCastStartForward() noexcept
{
	return GetActorForwardVector();
}

