// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GrimoireWidget.generated.h"

class UWrapBox;
class USpellSlotWidget;
class USpellLoaderSubsystem;
class UPlayerDataSubsystem;

UCLASS()
class WACKIER_WIZARDS_API UGrimoireWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnInitialized() override;
private:
	void SortIDs();

private:
	UPROPERTY()
	TObjectPtr<USpellLoaderSubsystem> _spellLoader;
	UPROPERTY()
	TObjectPtr<UPlayerDataSubsystem> _playerData;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USpellSlotWidget> _spellSlotDefault;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UWrapBox> _selectedGrid;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TArray<TObjectPtr<USpellSlotWidget>> _selectedSlots;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UWrapBox> _selectionGrid;
	UPROPERTY()
	TArray<TObjectPtr<USpellSlotWidget>> _selectionSlots;

	int _spellSlots;
	UPROPERTY(EditDefaultsOnly)
	int _selectedSlotsMax;

	UPROPERTY()
	TArray<int> _selectionIDs;
	UPROPERTY()
	TArray<int> _selectedIDs;
};
