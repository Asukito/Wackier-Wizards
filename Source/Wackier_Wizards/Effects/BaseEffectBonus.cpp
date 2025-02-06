// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffectBonus.h"
#include "EffectData.h"

void UBaseEffectBonus::Init(UEffectData* data, AActor* owner)
{
	effectOwner = owner;

	dataCopy = DuplicateObject(data, this);
	dataCopy->stackable = false;

	DoBonus();
}

void UBaseEffectBonus::DoBonus()
{
	dataCopy->MarkAsGarbage();
}
