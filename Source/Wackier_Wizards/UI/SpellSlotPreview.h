// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpellSlotPreview.generated.h"

class UTextBlock;

UCLASS()
class WACKIER_WIZARDS_API USpellSlotPreview : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(FText spellName);

private:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> _spellName;
};
