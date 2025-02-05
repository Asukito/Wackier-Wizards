// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEffect.h"
#include "../Components/EffectsComponent.h"
#include "../Interfaces/Effectable.h"

void UBaseEffect::StartEffect(AActor* actor, UEffectsComponent* list)
{
	_clearDelegate.BindUObject(list, &UEffectsComponent::QueueRemoval);

	if (IEffectable* Owner = Cast<IEffectable>(actor))
	{
		owner = Owner;
	}
	else
	{
		ClearEffect();
	}
}

void UBaseEffect::Update(float deltaTime)
{
	timer += deltaTime;
}

void UBaseEffect::EndEffect()
{
	ClearEffect();
}

void UBaseEffect::ClearEffect()
{
	_clearDelegate.ExecuteIfBound(this);
}
