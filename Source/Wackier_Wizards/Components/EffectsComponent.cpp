// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectsComponent.h"
#include "../Effects/OverTimeEffect.h"
#include "../Effects/InstantEffect.h"
#include "../Effects/DurationEffect.h"
#include "../Effects/BaseEffect.h"
#include "../Effects/EffectData.h"
#include "../Effects/ResultantEffectContainer.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEffectsComponent::UEffectsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UEffectsComponent::CreateAndAddEffect(UEffectData* effectData)
{
	TObjectPtr<UEffectData> data = nullptr;
	TObjectPtr<UBaseEffect> newEffect = nullptr;

	//Check if the effectData can interact with an effect contained within effects. If so, set data to the resulting effect.
	if (_resultantContainer != nullptr && _effects.Num() != 0)
	{
		data = CheckIfResultantValid(effectData);
	}

	//If a resulting effect doesn't occur, set the data to the effectData.
	if (data == nullptr)
	{
		data = effectData;
	}

	//Create the effect using the effectData
	switch (data->type)
	{
		case EffectType::OVERTIME:
			newEffect = NewObject<UOverTimeEffect>();

			break;
		case EffectType::INSTANT:
			newEffect = NewObject<UInstantEffect>();

			break;
		case EffectType::FOR_DURATION:
			newEffect = NewObject<UDurationEffect>();

			break;
	}

	if (newEffect == nullptr)
	{
		return;
	}

	//If stackable add effect no matter what
	if (data->stackable == true)
	{
		_effects.Add(newEffect);
		newEffect->StartEffect(data, GetOwner(), this);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Added Effect: %s"), *newEffect->GetEffectName()));
		return;
	}

	//If not stackable, check if effect exists in list, if so queue removal of the older effect
	if (UBaseEffect* effect = ReturnContains(data->name))
	{
		effect->EndEffect();
	}

	//Add the new effect
	_effects.Add(newEffect);
	newEffect->StartEffect(data, GetOwner(), this);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Added Effect: %s"), *newEffect->GetEffectName()));
}

void UEffectsComponent::QueueRemoval(UBaseEffect* effect)
{
	_toRemove.Add(effect);
}

void UEffectsComponent::ClearEffects()
{
	for (UBaseEffect* effect : _effects)
	{
		effect->EndEffect();
	}
}

void UEffectsComponent::RemoveEffects()
{
	for (UBaseEffect* effect : _toRemove)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Emerald, FString::Printf(TEXT("Removed Effect: %s"), *effect->GetEffectName()));
		_effects.Remove(effect);
	}

	_toRemove.Empty();
}

bool UEffectsComponent::Contains(FString name)
{
	for (UBaseEffect* effect : _effects)
	{
		if (name == effect->GetEffectName())
		{
			return true;
		}
	}

	return false;
}

UBaseEffect* UEffectsComponent::ReturnContains(FString name)
{
	for (UBaseEffect* effect : _effects)
	{
		if (name == effect->GetEffectName())
		{
			return effect;
		}
	}

	return nullptr;
}

UEffectData* UEffectsComponent::CheckIfResultantValid(UEffectData* effectData)
{
	for (TObjectPtr<UBaseEffect> effect : _effects)
	{
		if (TObjectPtr<UEffectData> data = _resultantContainer->CheckIfValid(effect->GetEffectName(), effectData->name))
		{
			QueueRemoval(effect);
			return data;
		}
	}

	return nullptr;
}


// Called when the game starts
void UEffectsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_resultantContainer = Cast<AResultantEffectContainer>(UGameplayStatics::GetActorOfClass(GetWorld(), AResultantEffectContainer::StaticClass()));
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

