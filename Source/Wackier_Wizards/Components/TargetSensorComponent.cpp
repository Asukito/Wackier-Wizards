// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetSensorComponent.h"
#include "../Characters/AI/GOAP/GOAP_Agent.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UTargetSensorComponent::UTargetSensorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_sensor = CreateDefaultSubobject<USphereComponent>(TEXT("Target Sensor"));
	checkf(_sensor, TEXT("TargetSensorComponent SphereComponent failed to intitialise"));
}

void UTargetSensorComponent::Init(float radius, TObjectPtr<UGOAP_Agent> agent)
{
	_sensor->SetSphereRadius(radius);

	_agent = agent;
	_radius = radius;
}

void UTargetSensorComponent::SetTarget(TObjectPtr<AActor> target)
{
	_target = target;
}

void UTargetSensorComponent::AttachTo(USceneComponent* component)
{
	_sensor->AttachToComponent(component, FAttachmentTransformRules::KeepRelativeTransform);
}

void UTargetSensorComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == _target)
	{
		_agent->SetIsTargetTooClose(true);
	}
}

void UTargetSensorComponent::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == _target)
	{
		_agent->SetIsTargetTooClose(false);
	}
}


// Called when the game starts
void UTargetSensorComponent::BeginPlay()
{
	Super::BeginPlay();

	_sensor->OnComponentBeginOverlap.AddDynamic(this, &UTargetSensorComponent::BeginOverlap);
	_sensor->OnComponentEndOverlap.AddDynamic(this, &UTargetSensorComponent::EndOverlap);
}


// Called every frame
void UTargetSensorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

