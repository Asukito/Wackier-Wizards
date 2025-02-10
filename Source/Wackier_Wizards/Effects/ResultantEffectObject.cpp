// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultantEffectObject.h"
#include "ResultantEffectData.h"
#include "EffectData.h"

void UResultantEffectObject::Init(UResultantEffectData* data)
{
	_effectOne = data->conditionOne;
	_effectTwo = data->conditionTwo;

	_resultantEffect = data->resultantEffect;
}

UEffectData* UResultantEffectObject::CheckIfValid(FString nameOne, FString nameTwo)
{
	if (nameOne == _effectOne->name)
	{
		if (nameTwo == _effectTwo->name)
		{
			return _resultantEffect;
		}
	}

	if (nameOne == _effectTwo->name)
	{
		if (nameTwo == _effectOne->name)
		{
			return _resultantEffect;
		}
	}

	return nullptr;
}
