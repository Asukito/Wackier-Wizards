// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSelectWidget.generated.h"

class USpellSlotWidget;
class UTextBlock;
class UWrapBox;
class APlayerCharacter;
class UUIManagerSubsystem;

UCLASS()
class WACKIER_WIZARDS_API UQuickSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetPlayer(APlayerCharacter* player);
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void ChangeSpell(int spellSlot);

private:	
	UPROPERTY()
	TObjectPtr<APlayerCharacter> _player;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USpellSlotWidget> _spellSlotDefault;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UWrapBox> _slotGrid;

	UPROPERTY()
	TArray<TObjectPtr<USpellSlotWidget>> _spellSlots;

	UPROPERTY()
	TArray<int> _spellIDs;

	UPROPERTY()
	TObjectPtr<UUIManagerSubsystem> _uiManager;
};
