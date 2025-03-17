// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellSlotPreview.h"
#include "Components/TextBlock.h"

void USpellSlotPreview::Init(FText spellName)
{
	_spellName->SetText(spellName);
}