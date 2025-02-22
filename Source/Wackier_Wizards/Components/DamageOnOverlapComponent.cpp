// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageOnOverlapComponent.h"
#include "Components/BoxComponent.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/Damageable.h"

// Sets default values for this component's properties
UDamageOnOverlapComponent::UDamageOnOverlapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	checkf(_collider, TEXT("DamageOnOverlapComponent Box Collider failed to intialise"));
	_collider->SetCollisionProfileName(FName("OverlapAll"));
}

void UDamageOnOverlapComponent::Init()
{
	_collider->SetupAttachment(GetOwner()->GetRootComponent());
}

void UDamageOnOverlapComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IHealth* target = Cast<IHealth>(OtherActor))
	{
		if (IDamageable* damageable = Cast<IDamageable>(OtherActor))
		{
			int percentage = target->GetHealth(true);

			if (percentage > 15)
			{
				damageable->TakeDamage((target->GetHealth(false) * (_damagePercent / 100)), GetOwner()->GetName());
				target->Respawn(false);
			}
			else
			{
				damageable->Kill();
			}
		}
	}
}


// Called when the game starts
void UDamageOnOverlapComponent::BeginPlay()
{
	Super::BeginPlay();

	_collider->OnComponentBeginOverlap.AddDynamic(this, &UDamageOnOverlapComponent::BeginOverlap);
	
}


// Called every frame
void UDamageOnOverlapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

