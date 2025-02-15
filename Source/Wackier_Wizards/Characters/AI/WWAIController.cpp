// Fill out your copyright notice in the Description page of Project Settings.


#include "WWAIController.h"
#include "Navigation/PathFollowingComponent.h"

void AWWAIController::SetDestination(const FVector destination)
{
	_currentDestination = destination;

	FAIMoveRequest moveTo;
	moveTo.SetAcceptanceRadius(50);
	moveTo.SetGoalLocation(_currentDestination);

	MoveTo(moveTo);
}

void AWWAIController::SetPauseMovement(bool val)
{
	if (val == true)
	{
		PauseMove(FAIRequestID::CurrentRequest);
		return;
	}

	ResumeMove(FAIRequestID::CurrentRequest);
}

void AWWAIController::ClearDestination()
{
	_currentDestination = FVector::ZeroVector;
	StopMovement();
}

FVector AWWAIController::GetCurrentDestination() const
{
	return _currentDestination;
}

bool AWWAIController::HasPath() const
{
	return _currentDestination != FVector::ZeroVector;
}
