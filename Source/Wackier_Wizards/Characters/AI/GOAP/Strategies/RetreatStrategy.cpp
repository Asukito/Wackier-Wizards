// Fill out your copyright notice in the Description page of Project Settings.


#include "RetreatStrategy.h"
#include "../GOAP_Agent.h"

void URetreatStrategy::Start(UGOAP_Agent* agent)
{
	_agent = agent;
	_agent->SetSeekPlayer(true);
	_agent->SetToRetreat(true);
}

void URetreatStrategy::Update(float deltaTime)
{	
	//If an enemy is blocking los, return.
	if (_agent->CheckForEnemyLOS() == true)
	{
		return;
	}

	//Attempt to attack player
	_agent->Attack();
}

void URetreatStrategy::Stop()
{
	_agent->SetSeekPlayer(false);
}

bool URetreatStrategy::Complete()
{
	return (_agent->TargetIsTooClose() == false || _agent->HasLineOfSight() == false);
}
