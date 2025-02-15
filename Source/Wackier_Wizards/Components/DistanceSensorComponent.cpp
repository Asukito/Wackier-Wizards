// Fill out your copyright notice in the Description page of Project Settings.


#include "DistanceSensorComponent.h"
#include "../Characters/AI/GOAP/GOAP_Agent.h"

// Sets default values for this component's properties
UDistanceSensorComponent::UDistanceSensorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDistanceSensorComponent::Init(float distance, TObjectPtr<UGOAP_Agent> agent)
{
	_distance = distance;
	_agent = agent;
}

void UDistanceSensorComponent::SetTarget(TObjectPtr<AActor> target)
{
	_target = target;
}

bool UDistanceSensorComponent::CheckDistanceToTarget()
{
	if (_target == nullptr)
	{
		return false;
	}

	FVector distance = _target->GetActorLocation() - _agent->GetOwner()->GetActorLocation();
	float length = distance.Length();

	if (length < _distance)
	{
		return true;
	}

	return false;
}

// Called when the game starts
void UDistanceSensorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UDistanceSensorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_agent->SetIsTargetInRange(CheckDistanceToTarget());
}

