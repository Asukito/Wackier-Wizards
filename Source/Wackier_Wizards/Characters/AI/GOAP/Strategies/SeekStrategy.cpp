// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekStrategy.h"
#include "../GOAP_Agent.h"

void USeekStrategy::Start(UGOAP_Agent* agent)
{
	_agent = agent;
	_agent->SetSeekPlayer(true);
}

void USeekStrategy::Update(float deltaTime)
{
	if (_agent->HasPath() == false)
	{
		_agent->SetSeekPlayer(true);
	}
}

void USeekStrategy::Stop()
{
	_agent->SetSeekPlayer(false);
}

bool USeekStrategy::Complete()
{
	return _agent->HasLineOfSight();
}
