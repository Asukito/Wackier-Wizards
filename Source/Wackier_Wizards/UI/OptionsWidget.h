// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsWidget.generated.h"

class UButton;
class UBorder;
class UTextBlock;
class USlider;

UCLASS()
class WACKIER_WIZARDS_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void CloseOptions();

	UFUNCTION()
	void DisplayInputOptions();
	UFUNCTION()
	void UpdateXSensitivity(float val);
	UFUNCTION()
	void UpdateYSensitivity(float val);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _closeOptionsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget), meta = (Category = "Input"))
	TObjectPtr<UButton> _inputButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget), meta = (Category = "Input"))
	TObjectPtr<UBorder> _inputBox;
	UPROPERTY(EditAnywhere, meta = (BindWidget), meta = (Category = "Input"))
	TObjectPtr<UTextBlock> _xText;
	UPROPERTY(EditAnywhere, meta = (BindWidget), meta = (Category = "Input"))
	TObjectPtr<UTextBlock> _yText;
	UPROPERTY(EditAnywhere, meta = (BindWidget), meta = (Category = "Input"))
	TObjectPtr<USlider> _xSensSlider;
	UPROPERTY(EditAnywhere, meta = (BindWidget), meta = (Category = "Input"))
	TObjectPtr<USlider> _ySensSlider;
};
