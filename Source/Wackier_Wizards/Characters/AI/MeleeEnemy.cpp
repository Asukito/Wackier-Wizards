// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeEnemy.h"
#include "../Player/PlayerCharacter.h"

AMeleeEnemy::AMeleeEnemy() : ABaseEnemy()
{
}

void AMeleeEnemy::Attack(IDamageable* target)
{
	if (_timer > 0.0f || target == nullptr)
	{
		return;
	}

	target->TakeDamage(_meleeDamage, "Melee NPC");
	_timer = _meleeDelay;
}

void AMeleeEnemy::BeginPlay()
{
	ABaseEnemy::BeginPlay();
}

void AMeleeEnemy::Tick(float DeltaTime)
{
	ABaseEnemy::Tick(DeltaTime);

	if (player.IsValid() == false)
	{
		return;
	}
	
	_timer -= DeltaTime;

	const FVector distance = player->GetActorLocation() - GetActorLocation();

	if (distance.Length() <= _meleeRange)
	{
		Attack(player->GetDamageableAccess());
	}
}

