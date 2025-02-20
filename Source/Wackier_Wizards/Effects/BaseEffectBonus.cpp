// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffectBonus.h"
#include "EffectData.h"

void UBaseEffectBonus::Init(UEffectData* data, AActor* owner, bool createCopy)
{
	effectOwner = owner;
	
	//Duplicates the effect data and sets the stackable boolean to false (to prevent bonus stacks, as this could lead to unlimited effects).
	effectData = DuplicateObject(data, this);
	effectData->stackable = false;

	//If the effectData copy is AOE, remove the bonus effect.
	if (effectData->bonus == EffectBonusType::AOE)
	{
		effectData->bonus = EffectBonusType::NONE;
	}

	DoBonus();
}

void UBaseEffectBonus::DoBonus()
{
	effectData->MarkAsGarbage();
}
