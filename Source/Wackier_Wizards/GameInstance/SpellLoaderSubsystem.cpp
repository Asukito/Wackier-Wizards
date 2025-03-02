// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellLoaderSubsystem.h"
#include "../Level/StageData.h"
#include "../Spells/SpellFactory.h"
#include "../Interfaces/Spell.h"

USpellData* USpellLoaderSubsystem::GetSpellData(FName spellRow)
{
	if (_spellDataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Failed to load SpellData")));
		return nullptr;
	}

	static const FString ContextString(TEXT("Spell Context String"));
	FSpellTableData* spellData = _spellDataTable->FindRow<FSpellTableData>(spellRow, ContextString, true);

	if (spellData != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Loaded %s spellData"), *spellRow.ToString()));
		return spellData->spellData;
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Failed to load %s spellData"), *spellRow.ToString()));
	return nullptr;
}


FSpellTableData* USpellLoaderSubsystem::GetSpellTableData(FName spellRow)
{
	if (_spellDataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Failed to load SpellData")));
		return nullptr;
	}

	static const FString ContextString(TEXT("Spell Context String"));
	FSpellTableData* spellData = _spellDataTable->FindRow<FSpellTableData>(spellRow, ContextString, true);

	if (spellData != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Loaded %s data"), *spellRow.ToString()));
		return spellData;
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Failed to load %s data"), *spellRow.ToString()));
	return nullptr;
}

ISpell* USpellLoaderSubsystem::CreateSpell(USpellData* data, ISpellCaster* owner)
{
	if (data == nullptr || owner == nullptr)
	{
		return nullptr;
	}

	if (_spellFactory == nullptr)
	{
		_spellFactory = NewObject<USpellFactory>();
	}

	return _spellFactory->CreateSpell(data, owner);
}

void USpellLoaderSubsystem::LoadDataTable()
{
	FSoftObjectPath path(TEXT("/Script/Engine.DataTable'/Game/1WWDEV/Ben-H/SpellData/DT_SpellData.DT_SpellData'"));
	UObject* pathObject = path.ResolveObject();

	if (pathObject == nullptr)
	{
		pathObject = path.TryLoad();
	}

	if (pathObject != nullptr)
	{
		_spellDataTable = Cast<UDataTable>(pathObject);
		UE_LOG(LogTemp, Warning, TEXT("Stage Loader Succeeded"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Stage Loader Failed"));
	}
}

void USpellLoaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USpellLoaderSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool USpellLoaderSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}

	return false;
}
