// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP_Goal.h"
#include "GOAP_Belief.h"

UGOAP_Goal::UGOAP_Goal()
{
}

//Iterates through the desiredEffects and evaluates them. If any evaluations return false, the goal has not been achieved.
bool UGOAP_Goal::CheckIfFulfilled()
{
	if (_desiredEffects.Num() == 0)
	{
		return true;
	}

	for (UGOAP_Belief* belief : _desiredEffects)
	{
		if (belief->Evaluate() == false)
		{
			return false;
		}
	}

	return true;
}
