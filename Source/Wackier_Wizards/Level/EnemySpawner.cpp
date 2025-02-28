// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawnPoint.h"
#include "../Level/WaveData.h"
#include "../Characters/AI/MeleeEnemy.h"

AEnemySpawner::AEnemySpawner()
{ 	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemySpawner::InitSpawner(UWorld* world, TFunction<FWaveData*()> delegate, TFunction<void()> onCompleteDelegate)
{
	_nextWave.BindLambda(delegate);
	_completeDelegate.BindLambda(onCompleteDelegate);

	TArray<AActor*> sps;

	if (world == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("NO WORLD")));
	}

	UGameplayStatics::GetAllActorsOfClass(world, AEnemySpawnPoint::StaticClass(), sps);

	if (sps.Num() == 0)
	{
		return;
	}

	for (TObjectPtr<AActor> actor : sps)
	{
		_spawnPoints.Add(Cast<AEnemySpawnPoint>(actor));
	}

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("%i"), _spawnPoints.Num()));

	GetNextWave();

	_spawnTimer = 2.0f;
	_isActive = true;
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_isActive == false)
	{
		return;
	}

	if (_toSpawn > 0)
	{
		_spawnTimer -= DeltaTime;

		if (_spawnTimer <= 0)
		{
			SpawnEnemy();
		}
	}
	else
	{
		if (_enemies.Num() == 0)
		{
			GetNextWave();
		}
	}
}

void AEnemySpawner::SpawnEnemy()
{
	if (_spawnPoints.Num() == 0)
	{
		return;
	}

	TArray<TObjectPtr<AEnemySpawnPoint>> activePoints;

	for (TObjectPtr<AEnemySpawnPoint> point : _spawnPoints)
	{
		if (point->IsActive() == true)
		{
			activePoints.Add(point);
		}
	}

	if (activePoints.Num() == 0)
	{
		return;
	}

	AEnemySpawnPoint* sp = activePoints[FMath::RandRange(0, activePoints.Num() - 1)];

	const FVector location = sp->GetActorLocation();

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TObjectPtr<AMeleeEnemy> enemy = GetWorld()->SpawnActor<AMeleeEnemy>(_defaultMeleeEnemy, location, FRotator::ZeroRotator, params);

	if (enemy != nullptr)
	{
		enemy->BindOnDeathDelegate([this, enemy]() { _enemies.Remove(enemy); });
		_enemies.Add(enemy);
		_toSpawn -= 1;
		_spawnTimer = 2.0f;
	}
}

void AEnemySpawner::GetNextWave()
{
	if (_nextWave.IsBound() == false)
	{
		return;
	}

	FWaveData* data = _nextWave.Execute();

	if (data == nullptr)
	{
		//Stage complete logic
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("STAGE COMPLETE")));
		_completeDelegate.ExecuteIfBound();

		return;
	}

	_meleeEnemies = data->meleeEnemies;
	_rangedEnemies = 0;

	_toSpawn = _meleeEnemies + _rangedEnemies;

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("NEXT WAVE")));
}
