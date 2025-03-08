// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseMenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../GameInstance/UIManagerSubsystem.h"
#include "../GameInstance/StageLoaderSubsystem.h"
#include "../Gamemodes/StageGameMode.h"
#include "../Gamemodes/HubGameMode.h"

void UPauseMenuWidget::NativeConstruct()
{
	if (Cast<AStageGameMode>(GetWorld()->GetAuthGameMode()))
	{
		_resetStageButton->SetIsEnabled(true);
		_resetStageButton->SetVisibility(ESlateVisibility::Visible);
		_stageText->SetVisibility(ESlateVisibility::HitTestInvisible);

		_returnToHUBButton->SetIsEnabled(true);
		_returnToHUBButton->SetVisibility(ESlateVisibility::Visible);
		_hubText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		_resetStageButton->SetIsEnabled(false);
		_resetStageButton->SetVisibility(ESlateVisibility::Hidden);
		_stageText->SetVisibility(ESlateVisibility::Hidden);

		_returnToHUBButton->SetIsEnabled(false);
		_returnToHUBButton->SetVisibility(ESlateVisibility::Hidden);
		_hubText->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UPauseMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	_continueButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Continue);
	_returnToHUBButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ReturnToHUB);
	_resetStageButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::ResetStage);
	_optionsButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Options);
	_quitButton->OnClicked.AddDynamic(this, &UPauseMenuWidget::Quit);
}

void UPauseMenuWidget::Continue()
{
	if (TObjectPtr<UUIManagerSubsystem> uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		uiManager->RemoveFromViewport(EWidgetType::PAUSE_MENU, GetOwningPlayer());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pause Menu couldn't get UI Manager"));
	}
}

void UPauseMenuWidget::ReturnToHUB()
{
	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		stageLoader->LoadHub();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pause Menu couldn't get Stage Loader"));
	}
}

void UPauseMenuWidget::ResetStage()
{
	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		stageLoader->ResetStage();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pause Menu couldn't get Stage Loader"));
	}
}

void UPauseMenuWidget::Options()
{
	if (TObjectPtr<UUIManagerSubsystem> uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		uiManager->AddToViewport(EWidgetType::OPTIONS, GetOwningPlayer());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Pause Menu couldn't get UI Manager"));
	}
}

void UPauseMenuWidget::Quit()
{
#if WITH_EDITOR
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Silver, FString::Printf(TEXT("QUIT")));
#else
	FGenericPlatformMisc::RequestExit(false);
#endif
}
