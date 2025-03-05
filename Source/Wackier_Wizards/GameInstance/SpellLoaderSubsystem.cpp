// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellLoaderSubsystem.h"
#include "../Level/StageData.h"
#include "../Spells/SpellFactory.h"
#include "../Interfaces/Spell.h"

USpellData* USpellLoaderSubsystem::GetSpellData(int id)
{
	if (_spellMap.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap is empty"));
		return nullptr;
	}

	if (id == 0)
	{
		return nullptr;
	}

	if (_spellMap.Contains(id) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap doesn't contain ID %i"), id);
		return nullptr;
	}

	return _spellMap[id]->spellData;
}


TArray<int> USpellLoaderSubsystem::GetSpellIDs()
{
	if (_spellMap.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap is empty"));
		return TArray<int>();
	}

	TArray<int> ids;
	_spellMap.GetKeys(ids);

	return ids;
}

UTexture2D* USpellLoaderSubsystem::GetSpellIcon(int id)
{
	if (_spellMap.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap is empty"));
		return nullptr;
	}

	if (id == 0)
	{
		return nullptr;
	}

	if (_spellMap.Contains(id) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap doesn't contain ID %i"), id);
		return nullptr;
	}

	return _spellMap[id]->spellIcon;
}

bool USpellLoaderSubsystem::GetSpellTableData(int id, FSpellTableData& OutData)
{
	if (_spellMap.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap is empty"));
		return false;
	}

	if (id == 0)
	{
		return false;
	}

	if (_spellMap.Contains(id) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap doesn't contain ID %i"), id);
		return false;
	}

	OutData = *_spellMap[id];
	return true;
}

FString USpellLoaderSubsystem::GetSpellName(int id)
{
	if (_spellMap.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap is empty"));
		return FString(" ");
	}

	if (id == 0)
	{
		return FString(" ");
	}

	if (_spellMap.Contains(id) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap doesn't contain ID %i"), id);
		return FString(" ");
	}

	return _spellMap[id]->spellName.ToString();
}

FString USpellLoaderSubsystem::GetSpellDescription(int id)
{
	if (_spellMap.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap is empty"));
		return FString(" ");
	}

	if (id == 0)
	{
		return FString(" ");
	}

	if (_spellMap.Contains(id) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("SpellMap doesn't contain ID %i"), id);
		return FString(" ");
	}

	return _spellMap[id]->spellDescription;
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
	if (_spellDataTable != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpellLoader has already loaded the SpellDataTable"));
		return;
	}

	FSoftObjectPath path(TEXT("/Script/Engine.DataTable'/Game/1WWDEV/Ben-H/SpellData/DT_SpellData.DT_SpellData'"));
	UObject* pathObject = path.ResolveObject();

	if (pathObject == nullptr)
	{
		pathObject = path.TryLoad();
	}

	if (pathObject != nullptr)
	{
		_spellDataTable = Cast<UDataTable>(pathObject);

		static const FString ContextString(TEXT("Spell Context String"));

		TArray<FSpellTableData*> spellStructs;
		_spellDataTable->GetAllRows(ContextString, spellStructs);

		for (FSpellTableData* data : spellStructs)
		{
			if (_spellMap.Contains(data->spellID) == true)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("Spell ID %i is repeated"), data->spellID));
				UE_LOG(LogTemp, Error, TEXT("Spell ID %i is repeated"), data->spellID);
				continue;
			}

			_spellMap.Add(data->spellID, data);
		}

		UE_LOG(LogTemp, Warning, TEXT("Spell Loader Succeeded"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Spell Loader Failed"));
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
