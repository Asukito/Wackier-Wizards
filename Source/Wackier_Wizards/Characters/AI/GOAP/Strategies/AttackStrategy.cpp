// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackStrategy.h"
#include "../GOAP_Agent.h"

void UAttackStrategy::Start(UGOAP_Agent* agent)
{
    _agent = agent;
    _player = _agent->GetPlayerActor();
    agent->SetFocus(_player.Get());
}

void UAttackStrategy::Update(float deltaTime)
{
    //If an enemy is blocking los, return.
    if (_agent->CheckForEnemyLOS() == true)
    {
        return;
    }
    
    //Attacking enemy shouldn't be pathing, reset if pathing.
    if (_agent->HasPath() == true)
    {
        _agent->SetSeekPlayer(false);
        _agent->SetFocus(_player.Get());
    }

    //Attempt to attack the player
    _agent->Attack();
}

void UAttackStrategy::Stop()
{
    _agent->ClearFocus();
}

bool UAttackStrategy::Complete()
{
    return (_agent->TargetIsInRange() == false || _agent->TargetIsTooClose() == true || _agent->HasLineOfSight() == false);
}
