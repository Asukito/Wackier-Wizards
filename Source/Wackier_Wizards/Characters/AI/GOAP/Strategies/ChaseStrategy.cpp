// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseStrategy.h"
#include "../GOAP_Agent.h"

void UChaseStrategy::Start(UGOAP_Agent* agent)
{
	_agent = agent;
	_agent->SetSeekPlayer(true);
}

//Attempts to attack the player while chasing
void UChaseStrategy::Update(float deltaTime)
{
	//If an enemy is blocking los, return.
	if (_agent->CheckForEnemyLOS() == true)
	{
		return;
	}

	//Attempt to attack player
	_agent->Attack();
}

void UChaseStrategy::Stop()
{
	_agent->SetSeekPlayer(false);
}

bool UChaseStrategy::Complete()
{
	return (_agent->TargetIsInRange() || _agent->HasLineOfSight() == false);
}
