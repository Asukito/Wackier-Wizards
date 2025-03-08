// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class WACKIER_WIZARDS_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void Continue();
	UFUNCTION()
	void ReturnToHUB();
	UFUNCTION()
	void ResetStage();
	UFUNCTION()
	void Options();
	UFUNCTION()
	void Quit();

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _continueButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _returnToHUBButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _resetStageButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _optionsButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _quitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> _hubText;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> _stageText;
};
