// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackStrategy.h"
#include "../GOAP_Agent.h"

void UAttackStrategy::Start(UGOAP_Agent* agent)
{
    _agent = agent;
    _player = _agent->GetPlayerActor();
}

void UAttackStrategy::Update(float deltaTime)
{
    FRotator lookAt = (_player->GetActorLocation() - _agent->GetActorLocation()).Rotation();
    _agent->GetOwner()->SetActorRotation(lookAt);

    _agent->Attack();
}

void UAttackStrategy::Stop()
{
}

bool UAttackStrategy::Complete()
{
    return (_agent->TargetIsInRange() == false || _agent->HasLineOfSight() == false);
}
