// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectsComponent.h"
#include "../Effects/BaseEffect.h"
#include "../Effects/BurnEffect.h"

// Sets default values for this component's properties
UEffectsComponent::UEffectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEffectsComponent::CreateAndAddEffect(Effect effect)
{
	UBaseEffect* newEffect;

	switch (effect)
	{
		case Effect::BURN:
			newEffect = NewObject<UBurnEffect>();
			_effects.Add(newEffect);
			newEffect->StartEffect(GetOwner(), this);

			break;
	}
}

void UEffectsComponent::AddEffect(UBaseEffect* effect)
{
	_effects.Add(effect);
	effect->StartEffect(GetOwner(), this);
}

void UEffectsComponent::QueueRemoval(UBaseEffect* effect)
{
	_toRemove.Add(effect);
}

void UEffectsComponent::RemoveEffects()
{
	for (UBaseEffect* effect : _toRemove)
	{
		_effects.Remove(effect);
	}

	_toRemove.Empty();
}


// Called when the game starts
void UEffectsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEffectsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_effects.IsEmpty() == true)
	{
		return;
	}

	for (UBaseEffect* effect : _effects)
	{
		effect->Update(DeltaTime);
	}

	if (_toRemove.IsEmpty() == false)
	{
		RemoveEffects();
	}
}

