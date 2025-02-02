#include "HealthComponent.h"
// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UHealthComponent::AdjustHealth(float amount)
{
	_health = FMath::Clamp(_health += amount, 0, _maxHealth);
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("%s Health Remaining: %i"), *GetOwner()->GetName(), GetHealth()));
}

int UHealthComponent::GetHealth() const
{
	return _health;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	_maxHealth = _baseHealth;
	_health = _maxHealth;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

