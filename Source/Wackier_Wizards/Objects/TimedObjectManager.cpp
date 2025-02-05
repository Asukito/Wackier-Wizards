// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedObjectManager.h"
#include "TimedPillar.h"

// Sets default values
ATimedObjectManager::ATimedObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimedObjectManager::BeginPlay()
{
	Super::BeginPlay();
	
	Init();
}

void ATimedObjectManager::Init()
{
	_index = 0;

	TArray<TObjectPtr<ATimedPillar>> pillars;
	_pillars.GenerateKeyArray(pillars);

	for (TObjectPtr<ATimedPillar> pillar : pillars)
	{
		if (_pillars[pillar] != _index)
		{
			pillar->SetIsActive(false);
		}
		else
		{
			pillar->SetIsActive(true);
		}
	}

	_hasInit = true;
}

void ATimedObjectManager::NextGroup()
{
	if (_index == _maxGroup)
	{
		_index = 0;
	}
	else
	{
		_index += 1;
	}

	TArray<TObjectPtr<ATimedPillar>> pillars;
	_pillars.GenerateKeyArray(pillars);

	for (TObjectPtr<ATimedPillar> pillar : pillars)
	{
		if (_pillars[pillar] != _index)
		{
			pillar->SetIsActive(false);
		}
		else
		{
			pillar->SetIsActive(true);
		}
	}
}

// Called every frame
void ATimedObjectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_timer += DeltaTime;

	if (_timer >= _delayBetweenSwitch)
	{
		NextGroup();
		_timer = 0.0f;
	}
}

