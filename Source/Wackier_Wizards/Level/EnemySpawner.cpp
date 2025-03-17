// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "EnemySpawnPoint.h"
#include "../Level/WaveData.h"
#include "../Characters/AI/MeleeEnemy.h"
#include "../Characters/AI/RangedEnemy.h"
#include "../Utility/ActorPool.h"

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
	if (_pool == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ENEMY SPAWNER HAS NO POOL")));
		return;
	}

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

	TObjectPtr<AEnemySpawnPoint> sp = activePoints[FMath::RandRange(0, activePoints.Num() - 1)];

	const FVector location = sp->GetActorLocation();

	if (TObjectPtr<ABaseEnemy> enemy = Cast<ABaseEnemy>(_pool->GetPoolActor(false, nullptr)))
	{
		enemy->SetActorLocation(location);
		enemy->SetActorHiddenInGame(false);

		enemy->BindOnDeathDelegate([this, enemy]() { KillEnemy(enemy); });
		_enemies.Add(enemy);
		_toSpawn -= 1;
		_spawnTimer = 2.0f;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("ENEMY SPAWNER HAS NON-ENEMY OBJECT IN POOL")));
	}
}

void AEnemySpawner::GetNextWave()
{
	if (_nextWave.IsBound() == false)
	{
		if (_pool != nullptr)
		{
			_pool->Release();
		}

		return;
	}

	FWaveData* data = _nextWave.Execute();

	if (data == nullptr)
	{
		if (_pool != nullptr)
		{
			_pool->Release();
		}

		//Stage complete logic
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("STAGE COMPLETE")));
		_completeDelegate.ExecuteIfBound();

		return;
	}
	_toSpawn = 0;

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TArray<TObjectPtr<AActor>> toPool;

	if (_defaultMeleeEnemy != nullptr)
	{
		for (int i = 0; i < data->meleeEnemies; i++)
		{
			toPool.Push(GetWorld()->SpawnActor<AMeleeEnemy>(_defaultMeleeEnemy, FVector::ZeroVector, FRotator::ZeroRotator, params));
			_toSpawn += 1;
		}
	}

	if (_defaultRangedEnemy != nullptr)
	{
		for (int i = 0; i < data->rangedEnemies; i++)
		{
			toPool.Push(GetWorld()->SpawnActor<ARangedEnemy>(_defaultRangedEnemy, FVector::ZeroVector, FRotator::ZeroRotator, params));
			_toSpawn += 1;
		}
	}

	//Do other enemies

	if (_pool == nullptr)
	{
		_pool = NewObject<UActorPool>();
	}
	else
	{
		_pool->Empty();
	}

	_pool->Populate(toPool);
	_pool->ShufflePool(1);

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("NEXT WAVE")));
}

void AEnemySpawner::KillEnemy(ABaseEnemy* enemy)
{
	_enemies.Remove(enemy);
	enemy->Destroy();
}
