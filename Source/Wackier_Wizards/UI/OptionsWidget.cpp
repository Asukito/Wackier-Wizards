// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionsWidget.h"
#include "Components/Button.h"
#include "Components/Border.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "../GameInstance/UIManagerSubsystem.h"

void UOptionsWidget::NativeConstruct()
{
	DisplayInputOptions();
}

void UOptionsWidget::NativeOnInitialized()
{
	_closeOptionsButton->OnClicked.AddDynamic(this, &UOptionsWidget::CloseOptions);
	_inputButton->OnClicked.AddDynamic(this, &UOptionsWidget::DisplayInputOptions);
	_xSensSlider->OnValueChanged.AddDynamic(this, &UOptionsWidget::UpdateXSensitivity);
	_ySensSlider->OnValueChanged.AddDynamic(this, &UOptionsWidget::UpdateYSensitivity);
}

void UOptionsWidget::CloseOptions()
{
	if (TObjectPtr<UUIManagerSubsystem> uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		uiManager->RemoveFromViewport(EWidgetType::OPTIONS, GetOwningPlayer());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Options Menu couldn't get UI Manager"));
	}
}

void UOptionsWidget::DisplayInputOptions()
{
	_inputBox->SetVisibility(ESlateVisibility::Visible);
}

void UOptionsWidget::UpdateXSensitivity(float val)
{
	FString string = "Horizontal Sensitivity: ";
	string.Append(FString::Printf(TEXT("%.2f"), val));
	_xText->SetText(FText::FromString(string));
}

void UOptionsWidget::UpdateYSensitivity(float val)
{
	FString string = "Vertical Sensitivity: ";
	string.Append(FString::Printf(TEXT("%.2f"), val));
	_yText->SetText(FText::FromString(string));
}
