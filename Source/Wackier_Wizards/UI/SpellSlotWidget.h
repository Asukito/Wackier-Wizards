// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpellSlotWidget.generated.h"

class UTextBlock;
class UButton;
class USpellLoaderSubsystem;
struct FEventReply;
class USpellLoaderSubsystem;

UCLASS()
class WACKIER_WIZARDS_API USpellSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(int id, USpellLoaderSubsystem* spellLoader);
	int GetID();

protected:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	FReply CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey);

	virtual void NativeOnInitialized() override;

private:
	UPROPERTY()
	TObjectPtr<USpellLoaderSubsystem> _spellLoader;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> _spellName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _selectButton;

	UPROPERTY()
	int _spellID;
};
