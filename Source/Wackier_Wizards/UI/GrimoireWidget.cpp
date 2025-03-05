// Fill out your copyright notice in the Description page of Project Settings.


#include "GrimoireWidget.h"
#include "SpellSlotWidget.h"
#include "../GameInstance/SpellLoaderSubsystem.h"
#include "../GameInstance/PlayerDataSubsystem.h"
#include "Components/WrapBox.h"

void UGrimoireWidget::NativePreConstruct()
{
	for (TObjectPtr<USpellSlotWidget> spellSlot : _selectionSlots)
	{
		spellSlot->Destruct();
	}

	for (TObjectPtr<USpellSlotWidget> spellSlot : _selectedSlots)
	{
		spellSlot->Destruct();
	}
}

void UGrimoireWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SortIDs();

	for (int i = 0; i < _spellSlots; i++)
	{
		TObjectPtr<USpellSlotWidget> spellSlot = CreateWidget<USpellSlotWidget>(this, _spellSlotDefault);

		if (i >= _selectionIDs.Num())
		{
			_selectionIDs.Add(0);
		}

		spellSlot->Init(_selectionIDs[i], _spellLoader);

		_selectionSlots.Add(spellSlot);
		_selectionGrid->AddChildToWrapBox(spellSlot);
	}

	for (int i = 0; i < _selectedSlotsMax; i++)
	{
		TObjectPtr<USpellSlotWidget> spellSlot = CreateWidget<USpellSlotWidget>(this, _spellSlotDefault);

		if (i >= _selectedIDs.Num())
		{
			_selectedIDs.Add(0);
		}

		spellSlot->Init(_selectedIDs[i], _spellLoader);

		_selectedSlots.Add(spellSlot);
		_selectedGrid->AddChildToWrapBox(spellSlot);
	}
}

void UGrimoireWidget::NativeDestruct()
{
	TArray<int> toSet;

	for (TObjectPtr<USpellSlotWidget> slot : _selectedSlots)
	{
		toSet.Add(slot->GetID());
	}

	_playerData->SetSpells(toSet);
}

void UGrimoireWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (TObjectPtr<USpellLoaderSubsystem> spellLoader = GetGameInstance()->GetSubsystem<USpellLoaderSubsystem>())
	{
		_spellLoader = spellLoader;
	}

	if (TObjectPtr<UPlayerDataSubsystem> playerData = GetGameInstance()->GetSubsystem<UPlayerDataSubsystem>())
	{
		_playerData = playerData;
	}
}

void UGrimoireWidget::SortIDs()
{
	if (_spellLoader == nullptr)
	{
		return;
	}

	_selectionIDs = _spellLoader->GetSpellIDs();
	_spellSlots = _selectionIDs.Num();

	if (_playerData == nullptr)
	{
		return;
	}

	_selectedIDs = _playerData->GetSavedSpellIDs();

	if (_selectedIDs.Num() > 0)
	{
		for (int id : _selectedIDs)
		{
			if (_selectionIDs.Contains(id))
			{
				_selectionIDs.Remove(id);
			}
		}
	}
}
