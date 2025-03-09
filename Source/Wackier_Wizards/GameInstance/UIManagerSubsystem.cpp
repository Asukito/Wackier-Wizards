// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManagerSubsystem.h"
#include "../UI/GrimoireWidget.h"
#include "../UI/QuickSelectWidget.h"
#include "../UI/PauseMenuWidget.h"
#include "../UI/OptionsWidget.h"
#include "../UI/StageCompleteWidget.h"
#include "../Characters/Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void UUIManagerSubsystem::CreateWidgets(APlayerController* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	if (_grimoireDefault != nullptr)
	{
		_grimoire = CreateWidget<UGrimoireWidget>(controller, _grimoireDefault);
		_widgets.Add(EWidgetType::GRIMOIRE, _grimoire);
		_addToViewportFunctions.Add(EWidgetType::GRIMOIRE, &UUIManagerSubsystem::AddGrimoireToViewport);
	}

	if (_quickSelectDefault != nullptr)
	{
		_quickSelect = CreateWidget<UQuickSelectWidget>(controller, _quickSelectDefault);

		if (TObjectPtr<APlayerCharacter> player = Cast<APlayerCharacter>(controller->GetCharacter()))
		{
			_quickSelect->SetPlayer(player);
		}

		_widgets.Add(EWidgetType::QUICK_SELECT, _quickSelect);
		_addToViewportFunctions.Add(EWidgetType::QUICK_SELECT, &UUIManagerSubsystem::AddQuickSelectToViewport);
	}

	if (_pauseMenuDefault != nullptr)
	{
		_pauseMenu = CreateWidget<UPauseMenuWidget>(controller, _pauseMenuDefault);
		_widgets.Add(EWidgetType::PAUSE_MENU, _pauseMenu);
		_addToViewportFunctions.Add(EWidgetType::PAUSE_MENU, &UUIManagerSubsystem::AddPauseMenuToViewport);
		_removeFromViewportFunctions.Add(EWidgetType::PAUSE_MENU, &UUIManagerSubsystem::RemovePauseMenuFromViewport);
	}

	if (_optionsMenuDefault != nullptr)
	{
		_optionsMenu = CreateWidget<UOptionsWidget>(controller, _optionsMenuDefault);
		_widgets.Add(EWidgetType::OPTIONS, _optionsMenu);
		_addToViewportFunctions.Add(EWidgetType::OPTIONS, &UUIManagerSubsystem::AddOptionsToViewport);
		_removeFromViewportFunctions.Add(EWidgetType::OPTIONS, &UUIManagerSubsystem::RemoveOptionsFromViewport);
	}

	if (_stageCompleteDefault != nullptr)
	{
		_stageCompleteWidget = CreateWidget<UStageCompleteWidget>(controller, _stageCompleteDefault);
		_widgets.Add(EWidgetType::STAGE_COMPLETE, _stageCompleteWidget);
		_addToViewportFunctions.Add(EWidgetType::STAGE_COMPLETE, &UUIManagerSubsystem::AddStageCompleteToViewport);
	}
}

void UUIManagerSubsystem::ToggleWidget(EWidgetType target, APlayerController* controller)
{
	if (_widgets.Contains(target) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager _widgets doesn't contain target"));

		return;
	}

	if (_widgets[target]->IsInViewport() == true)
	{
		RemoveFromViewport(target, controller);
	}
	else
	{
		AddToViewport(target, controller);
	}
}

void UUIManagerSubsystem::AddToViewport(EWidgetType target, APlayerController* controller)
{
	if (_addToViewportFunctions.Contains(target) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager _addToViewportFunctions doesn't contain target"));
		return;
	}

	if (_widgets[target]->IsInViewport() == true)
	{
		return;
	}

	_addToViewportFunctions[target](this, controller);
}

void UUIManagerSubsystem::RemoveFromViewport(EWidgetType target, APlayerController* controller)
{
	if (_widgets.Contains(target) == false)
	{
		UE_LOG(LogTemp, Error, TEXT("UIManager _widgets doesn't contain target"));
		return;
	}

	if (_widgets[target]->IsInViewport() == false)
	{
		return;
	}

	if (_removeFromViewportFunctions.Contains(target) == true)
	{
		_removeFromViewportFunctions[target](this, controller);
		return;
	}

	FInputModeGameOnly inputMode;
	controller->SetInputMode(inputMode);
	controller->SetShowMouseCursor(false);

	_widgets[target]->RemoveFromParent();
}

void UUIManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UUIManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

bool UUIManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}

	return false;
}

void UUIManagerSubsystem::AddGrimoireToViewport(APlayerController* controller)
{
	if (_grimoire == nullptr)
	{		
		UE_LOG(LogTemp, Error, TEXT("Grimoire Widget hasn't been assigned"));

		return;
	}

	_grimoire->AddToViewport();

	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(_grimoire->TakeWidget());
	controller->SetInputMode(inputMode);

	controller->SetShowMouseCursor(true);
}

void UUIManagerSubsystem::AddQuickSelectToViewport(APlayerController* controller)
{
	if (_quickSelect == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("QuickSelect Widget hasn't been assigned"));

		return;
	}

	_quickSelect->AddToViewport();

	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(_quickSelect->TakeWidget());
	controller->SetInputMode(inputMode);

	controller->SetShowMouseCursor(true);
}

void UUIManagerSubsystem::AddPauseMenuToViewport(APlayerController* controller)
{
	if (_pauseMenu == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PauseMenu Widget hasn't been assigned"));

		return;
	}

	ClearViewport(controller);

	_pauseMenu->AddToViewport();

	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(_pauseMenu->TakeWidget());
	controller->SetInputMode(inputMode);

	controller->SetShowMouseCursor(true);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UUIManagerSubsystem::RemovePauseMenuFromViewport(APlayerController* controller)
{
	if (_widgets[EWidgetType::OPTIONS]->IsInViewport() == true)
	{
		RemoveFromViewport(EWidgetType::OPTIONS, controller);
	}

	FInputModeGameOnly inputMode;
	controller->SetInputMode(inputMode);
	controller->SetShowMouseCursor(false);

	_widgets[EWidgetType::PAUSE_MENU]->RemoveFromParent();

	UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UUIManagerSubsystem::AddOptionsToViewport(APlayerController* controller)
{
	if (_optionsMenu == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Options Widget hasn't been assigned"));

		return;
	}

	_optionsMenu->AddToViewport();

	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(_optionsMenu->TakeWidget());
	controller->SetInputMode(inputMode);

	controller->SetShowMouseCursor(true);
}

void UUIManagerSubsystem::RemoveOptionsFromViewport(APlayerController* controller)
{
	FInputModeGameAndUI inputMode;
	inputMode.SetWidgetToFocus(_pauseMenu->TakeWidget());
	controller->SetInputMode(inputMode);

	_widgets[EWidgetType::OPTIONS]->RemoveFromParent();
}

void UUIManagerSubsystem::AddStageCompleteToViewport(APlayerController* controller)
{
	if (_stageCompleteWidget == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("StageComplete Widget hasn't been assigned"));

		return;
	}

	ClearViewport(controller);

	_stageCompleteWidget->AddToViewport();

	FInputModeUIOnly inputMode;
	inputMode.SetWidgetToFocus(_stageCompleteWidget->TakeWidget());
	controller->SetInputMode(inputMode);

	controller->SetShowMouseCursor(true);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void UUIManagerSubsystem::ClearViewport(APlayerController* controller)
{
	TArray<EWidgetType> widgets;
	_widgets.GetKeys(widgets);

	for (EWidgetType type : widgets)
	{
		RemoveFromViewport(type, controller);
	}
}
