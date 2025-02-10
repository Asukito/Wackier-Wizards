// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffectBonus.h"
#include "EffectData.h"

void UBaseEffectBonus::Init(UEffectData* data, AActor* owner, bool createCopy)
{
	effectOwner = owner;
	
	effectData = DuplicateObject(data, this);
	effectData->stackable = false;

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
