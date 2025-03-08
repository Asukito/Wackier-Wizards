// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageCompleteWidget.generated.h"

class UButton;
class UTextBlock;

UCLASS()
class WACKIER_WIZARDS_API UStageCompleteWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void ReturnToHUB();
	UFUNCTION()
	void ResetStage();
	UFUNCTION()
	void LoadNextStage();
private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> _stageText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _returnToHUBButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _resetStageButton;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _nextStageButton;

	int _stage;
};
