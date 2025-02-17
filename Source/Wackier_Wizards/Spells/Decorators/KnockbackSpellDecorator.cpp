// Fill out your copyright notice in the Description page of Project Settings.


#include "KnockbackSpellDecorator.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../SpellData.h"

void UKnockbackSpellDecorator::ProcessHit(AActor* hit, FVector location)
{
	spell->ProcessHit(hit, location);

	if (hit == nullptr)
	{
		return;
	}

	TArray<UCharacterMovementComponent*> components;
	hit->GetComponents<UCharacterMovementComponent>(components);

	if (components.Num() == 0)
	{
		return;
	}

	FVector direction = hit->GetActorLocation() - location;
	direction.Normalize();

	components[0]->Launch(direction * spellData->knockbackStrength);
}
