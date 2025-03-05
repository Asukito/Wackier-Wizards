// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellSlotWidget.h"
#include "Components/TextBlock.h"
#include "DragWidget.h"
#include "../GameInstance/SpellLoaderSubsystem.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "SpellSlotPreview.h"
#include "Components/Button.h"
#include "GrimoireWidget.h"

void USpellSlotWidget::Init(int id, USpellLoaderSubsystem* spellLoader, UGrimoireWidget* grimoire)
{
	if (spellLoader == nullptr || grimoire == nullptr)
	{
		return;
	}

	_selectButton->OnClicked.AddDynamic(this, &USpellSlotWidget::UpdateDisplayedSpell);

	_grimoire = grimoire;
	_spellLoader = spellLoader;

	ChangeID(id);
}

void USpellSlotWidget::ChangeID(int id)
{
	_spellID = id;
	_spellName->SetText(FText::FromString(_spellLoader->GetSpellName(id)));

	TObjectPtr<UTexture2D> icon = _spellLoader->GetSpellIcon(id);

	if (icon != nullptr)
	{
		_spellIcon->SetBrushFromTexture(icon);
	}
	else
	{
		_spellIcon->SetBrushFromMaterial(_emptyIcon);
	}

	_spellIcon->SetDesiredSizeOverride(_imageSize);
}

int USpellSlotWidget::GetID()
{
	return _spellID;
}

void USpellSlotWidget::UpdateDisplayedSpell()
{
	_grimoire->UpdateDisplayedSpell(_spellID);
}

FReply USpellSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);

	FEventReply reply;
	reply.NativeReply = NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return reply.NativeReply;
}

FReply USpellSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return CustomDetectDrag(InMouseEvent, this, EKeys::LeftMouseButton);
}

void USpellSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	TObjectPtr<UDragWidget> DragDropOperation = NewObject<UDragWidget>();
	DragDropOperation->widgetReference = this;
	DragDropOperation->dragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	TObjectPtr<USpellSlotPreview> preview = CreateWidget<USpellSlotPreview>(this, _previewDefault);
	preview->Init(_spellName->GetText());

	DragDropOperation->DefaultDragVisual = preview;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOperation;
}

bool USpellSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (TObjectPtr<UDragWidget> destinationSlot = Cast<UDragWidget>(InOperation))
	{
		if (TObjectPtr<USpellSlotWidget> spellSlot = Cast<USpellSlotWidget>(destinationSlot->widgetReference))
		{
			int destinationID = spellSlot->GetID();

			if (destinationID != _spellID)
			{
				spellSlot->ChangeID(_spellID);
				ChangeID(destinationID);
			}

			return true;
		}
	}

	return false;
}

FReply USpellSlotWidget::CustomDetectDrag(const FPointerEvent& InMouseEvent, UWidget* WidgetDetectingDrag, FKey DragKey)
{
	if (InMouseEvent.GetEffectingButton() == DragKey /*|| PointerEvent.IsTouchEvent()*/)
	{
		FEventReply Reply;
		Reply.NativeReply = FReply::Handled();

		if (WidgetDetectingDrag)
		{
			TSharedPtr<SWidget> SlateWidgetDetectingDrag = WidgetDetectingDrag->GetCachedWidget();
			if (SlateWidgetDetectingDrag.IsValid())
			{
				Reply.NativeReply = Reply.NativeReply.DetectDrag(SlateWidgetDetectingDrag.ToSharedRef(), DragKey);
				return Reply.NativeReply;
			}
		}
	}

	return FReply::Unhandled();
}
