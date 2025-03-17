// Fill out your copyright notice in the Description page of Project Settings.


#include "SeekerComponent.h"
#include "../Characters/AI/WWAIController.h"

// Sets default values for this component's properties
USeekerComponent::USeekerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USeekerComponent::SetSeekTarget(AActor* target)
{
	_target = target;
}

void USeekerComponent::ClearSeekTarget()
{
	_controller->ClearDestination();
	_target = nullptr;
	_toRetreat = false;
}

void USeekerComponent::SetController(AWWAIController* controller)
{
	_controller = controller;
}

void USeekerComponent::SetIsActive(bool isActive)
{
	_isActive = isActive;
}

void USeekerComponent::SetToRetreat(bool val)
{
	_toRetreat = val;
}

// Called every frame
void USeekerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_isActive == false || _controller.IsValid() == false || _target == nullptr)
	{
		return;
	}

	//If retreating, take the direction to the target from the current location
	if (_toRetreat == true)
	{
		FVector location = GetOwner()->GetActorLocation();
		FVector direction = _target->GetActorLocation() - location;

		_controller->SetDestination(location - direction);
		return;
	}

	_controller->SetDestination(_target->GetActorLocation());
}

