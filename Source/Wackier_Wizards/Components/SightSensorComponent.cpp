// Fill out your copyright notice in the Description page of Project Settings.


#include "SightSensorComponent.h"
#include "../Characters/AI/GOAP/GOAP_Agent.h"

// Sets default values for this component's properties
USightSensorComponent::USightSensorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USightSensorComponent::Init(TObjectPtr<UGOAP_Agent> agent)
{
	_agent = agent;
}

void USightSensorComponent::SetTarget(TObjectPtr<AActor> target)
{
	_target = target;
}

bool USightSensorComponent::Scan()
{
	//Checks if the distance between the actor and target is greater than the seeable distance
	FVector dir = _target->GetActorLocation() - _agent->GetActorLocation();

	if (dir.Length() > _distance)
	{
		return false;
	}

	dir.Normalize();

	//Checks to see if the target is in the owners FOV
	FVector forward = _agent->GetForwardVector();

	if (forward.Dot(dir) < (1 - _fov))
	{
		return false;
	}

	//Finally, creates a linetrace from the owner to the target, if an actor that isn't the target blocks the linetrace, the target is not in sight.
	FHitResult hit;
	FCollisionQueryParams params;
	params.AddIgnoredActor(_agent->GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(hit, _agent->GetOwner()->GetActorLocation(), _target->GetActorLocation(), ECC_Visibility, params))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Sight: %s"), hit.GetActor() ? *hit.GetActor()->GetName() : TEXT("Nothing")));
		//DrawDebugLine(GetWorld(), _agent->GetOwner()->GetActorLocation(), hit.GetActor()->GetActorLocation(), FColor::Green, false, 1.0f);

		if (hit.GetActor() == nullptr || hit.GetActor() != _target)
		{
			return false;
		}

		return true;
	};

	return false;
}


// Called when the game starts
void USightSensorComponent::BeginPlay()
{
	Super::BeginPlay();

	_timer = _scanInterval;
}

// Called every frame
void USightSensorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_target == nullptr)
	{
		return;
	}

	_timer += DeltaTime;

	if (_timer >= _scanInterval)
	{
		_agent->SetHasLineOfSight(Scan());
		_timer = 0;
	}
}

