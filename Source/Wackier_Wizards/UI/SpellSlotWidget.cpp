// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellSlotWidget.h"
#include "Components/TextBlock.h"
#include "DragWidget.h"
#include "../GameInstance/SpellLoaderSubsystem.h"

void USpellSlotWidget::Init(int id, USpellLoaderSubsystem* spellLoader)
{
	if (spellLoader == nullptr)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::Printf(TEXT("DESTINATION ID %i, NEW ID %i"), _spellID, id));

	_spellLoader = spellLoader;

	_spellID = id;
	_spellName->SetText(FText::FromString(_spellLoader->GetSpellName(id)));
}

int USpellSlotWidget::GetID()
{
	return _spellID;
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
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOperation;
}

void USpellSlotWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	//RemoveFromParent();
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
				spellSlot->Init(_spellID, _spellLoader);
				Init(destinationID, _spellLoader);
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

void USpellSlotWidget::NativeOnInitialized()
{
}
