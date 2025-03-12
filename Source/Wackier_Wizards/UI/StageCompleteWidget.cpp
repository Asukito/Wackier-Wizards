// Fill out your copyright notice in the Description page of Project Settings.


#include "StageCompleteWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../GameInstance/StageLoaderSubsystem.h"

void UStageCompleteWidget::NativeConstruct()
{
	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		_stage = stageLoader->GetStageLevel();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StageCompleteMenu couldn't get Stage Loader"));
	}

	FString string = "Stage Complete: ";
	string.Append(FString::FromInt(_stage));
	_stageText->SetText(FText::FromString(string));
}

void UStageCompleteWidget::NativeOnInitialized()
{
	_returnToHUBButton->OnClicked.AddDynamic(this, &UStageCompleteWidget::ReturnToHUB);
	_resetStageButton->OnClicked.AddDynamic(this, &UStageCompleteWidget::ResetStage);
	_nextStageButton->OnClicked.AddDynamic(this, &UStageCompleteWidget::LoadNextStage);
}

void UStageCompleteWidget::ReturnToHUB()
{
	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		stageLoader->LoadHub();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StageCompleteMenu couldn't get Stage Loader"));
	}
}

void UStageCompleteWidget::ResetStage()
{
	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		stageLoader->ResetStage();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StageCompleteMenu couldn't get Stage Loader"));
	}
}

void UStageCompleteWidget::LoadNextStage()
{
	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		stageLoader->LoadStage(_stage + 1);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StageCompleteMenu couldn't get Stage Loader"));
	}
}
