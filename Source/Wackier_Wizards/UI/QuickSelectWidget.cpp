// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSelectWidget.h"
#include "../GameInstance/PlayerDataSubsystem.h"
#include "../GameInstance/SpellLoaderSubsystem.h"
#include "../GameInstance/UIManagerSubsystem.h"
#include "SpellSlotWidget.h"
#include "Components/WrapBox.h"
#include "../Characters/Player/PlayerCharacter.h"

void UQuickSelectWidget::ChangeSpell(int spellSlot)
{
	if (_player == nullptr)
	{
		return;
	}

	if (_uiManager == nullptr)
	{
		_uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>();
	}

	for (int i = 0; i < _spellSlots.Num(); i++)
	{
		if ((i + 1) == spellSlot)
		{
			_spellSlots[i]->IsSelected(true);
			continue;
		}

		_spellSlots[i]->IsSelected(false);
	}

	_player->ChangeSpell(spellSlot);
	_uiManager->RemoveFromViewport(EWidgetType::QUICK_SELECT, Cast<APlayerController>(_player->GetController()));
}

void UQuickSelectWidget::SetPlayer(APlayerCharacter* player)
{
	_player = player;
}

void UQuickSelectWidget::NativeOnInitialized()
{
	if (TObjectPtr<UPlayerDataSubsystem> playerData = GetGameInstance()->GetSubsystem<UPlayerDataSubsystem>())
	{
		_spellIDs = playerData->GetSavedSpellIDs();

		if (TObjectPtr<USpellLoaderSubsystem> spellLoader = GetGameInstance()->GetSubsystem<USpellLoaderSubsystem>())
		{
			for (int i = 0; i < _spellIDs.Num(); i++)
			{
				TObjectPtr<USpellSlotWidget> spellSlot = CreateWidget<USpellSlotWidget>(this, _spellSlotDefault);

				if (spellSlot != nullptr)
				{
					spellSlot->InitQuickSelect(_spellIDs[i], spellLoader, [this](int slot) { ChangeSpell(slot); }, i + 1);
					_slotGrid->AddChild(spellSlot);
					_spellSlots.Add(spellSlot);

					if (i == 0)
					{
						spellSlot->IsSelected(true);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("QuickSelectWidget failed to initialise SpellLoader"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("QuickSelectWidget failed to initialise PlayerData"));
	}
}