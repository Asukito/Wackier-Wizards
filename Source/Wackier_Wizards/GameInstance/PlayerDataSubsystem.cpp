// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDataSubsystem.h"
#include "SpellLoaderSubsystem.h"

void UPlayerDataSubsystem::SetSpells(TArray<int> spellIDs)
{
	_spells = spellIDs;
}

TArray<int> UPlayerDataSubsystem::GetSavedSpellIDs()
{
	return _spells;
}

TArray<USpellData*> UPlayerDataSubsystem::GetSpellsAsData()
{
	TObjectPtr<USpellLoaderSubsystem> spellLoader = GetGameInstance()->GetSubsystem<USpellLoaderSubsystem>();
	TArray<TObjectPtr<USpellData>> spellData;

	if (spellLoader == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerDataSubsystem couldn't initialise SpellLoaderSubsystem"));
		return spellData;
	}

	for (int id : _spells)
	{
		if (id == 0)
		{
			spellData.Add(nullptr);
			continue;
		}

		spellData.Add(spellLoader->GetSpellData(id));
	}

	return spellData;
}

void UPlayerDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPlayerDataSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UPlayerDataSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}

	return false;
}
