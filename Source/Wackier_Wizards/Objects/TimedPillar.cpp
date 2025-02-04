// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedPillar.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATimedPillar::ATimedPillar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	checkf(_collider, TEXT("TimedPillar Collider failed to initialise"));
	_collider->SetUsingAbsoluteScale(true);

	_staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	checkf(_staticMesh, TEXT("TimedPillar Static Mesh failed to initialise"));
	_staticMesh->SetUsingAbsoluteScale(true);
}

void ATimedPillar::SetIsActive(bool val)
{
	_updateScale = true;
	_isActive = val;
}

// Called when the game starts or when spawned
void ATimedPillar::BeginPlay()
{
	Super::BeginPlay();
	
	_isActive = true;
	_startZ = _staticMesh->GetRelativeScale3D().Z;
}

// Called every frame
void ATimedPillar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_updateScale == false)
	{
		return;
	}

	if (_isActive == true)
	{
		if (_collider->IsCollisionEnabled() == false)
		{
			_collider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}

		if (_staticMesh->GetComponentScale().Z < _startZ)
		{
			_staticMesh->SetWorldScale3D(FVector(_staticMesh->GetComponentScale().X, _staticMesh->GetComponentScale().Y, _staticMesh->GetComponentScale().Z + (DeltaTime)));
		}
		else
		{
			_updateScale = false;
		}
	}
	else
	{
		if (_collider->IsCollisionEnabled() == true)
		{
			_collider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		if (_staticMesh->GetComponentScale().Z > 0)
		{
			_staticMesh->SetWorldScale3D(FVector(_staticMesh->GetComponentScale().X, _staticMesh->GetComponentScale().Y, _staticMesh->GetComponentScale().Z - (DeltaTime)));
		}
		else
		{
			_updateScale = false;
		}
	}
}

