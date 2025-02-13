// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeNPC.h"
#include "WWAIController.h"
#include "../Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/PathFollowingComponent.h"

// Sets default values
AMeleeNPC::AMeleeNPC() : ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMeleeNPC::BeginPlay()
{
	ABaseCharacter::BeginPlay();

	_controller = Cast<AWWAIController>(GetController());
	_player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AMeleeNPC::Attack(IDamageable* target)
{
	if (_timer <= _meleeDelay)
	{
		return;
	}

	target->TakeDamage(_meleeDamage, "Melee NPC");
	_timer = 0.0f;
}

// Called every frame
void AMeleeNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_player == nullptr)
	{
		return;
	}

	_timer += DeltaTime;

	const FVector destination = _player->GetSeekLocation();

	if (destination != FVector::ZeroVector)
	{
		_controller->SetDestination(destination);

		const FVector distance = destination - GetActorLocation();

		if (distance.Length() < _meleeRange)
		{
			Attack(Cast<IDamageable>(_player));
		}
	}
	else
	{
		_controller->ClearDestination();
	}
}

