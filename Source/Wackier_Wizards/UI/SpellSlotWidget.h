// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpellSlotWidget.generated.h"

class UTextBlock;
class UButton;
class USpellLoaderSubsystem;
class UBorder;
class USpellLoaderSubsystem;
class USpellSlotPreview;
class UImage;
class UGrimoireWidget;

UCLASS()
class WACKIER_WIZARDS_API USpellSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init(int id, USpellLoaderSubsystem* spellLoader, UGrimoireWidget* grimoire);
	void ChangeID(int id);
	int GetID();

	UFUNCTION()
	void UpdateDisplayedSpell();

protected:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	FReply CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey);

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UMaterial> _emptyIcon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USpellSlotPreview> _previewDefault;

	UPROPERTY()
	TObjectPtr<USpellLoaderSubsystem> _spellLoader;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UBorder> _border;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> _spellName;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> _selectButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> _spellIcon;

	UPROPERTY()
	TObjectPtr<UGrimoireWidget> _grimoire;

	int _spellID;
	UPROPERTY(EditAnywhere)
	FVector2D _imageSize;
};
