// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultantEffectObject.h"
#include "ResultantEffectData.h"
#include "../EffectData.h"

void UResultantEffectObject::Init(UResultantEffectData* data)
{
	_effectOne = data->conditionOne;
	_effectTwo = data->conditionTwo;

	_resultantEffect = data->resultantEffect;

	_isRandom = data->isRandom;
	_chance = data->chance;
}

UEffectData* UResultantEffectObject::CheckIfValid(FString nameOne, FString nameTwo)
{
	if (nameOne == _effectOne || nameOne == _effectTwo)
	{
		if (nameTwo == _effectTwo || nameTwo == _effectOne)
		{
			if (_isRandom == false)
			{
				return _resultantEffect;
			}

			float rand = FMath::RandRange(0, 100);

			if (rand < _chance)
			{
				return _resultantEffect;
			}
		}
	}

	return nullptr;
}
