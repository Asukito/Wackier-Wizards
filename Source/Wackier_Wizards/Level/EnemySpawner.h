// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

struct FWaveData;
class AEnemySpawnPoint;
class ABaseEnemy;
class AMeleeEnemy;
class ARangedEnemy;
class UActorPool;

DECLARE_DELEGATE_RetVal(FWaveData*, FNextWave);
DECLARE_DELEGATE(FOnComplete);

UCLASS()
class WACKIER_WIZARDS_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:
	AEnemySpawner();

	void InitSpawner(UWorld* world, TFunction<FWaveData*()> delegate, TFunction<void()> onCompleteDelegate);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void SpawnEnemy();
	void GetNextWave();
	
	void KillEnemy(ABaseEnemy* enemy);
private:
	UPROPERTY()
	TObjectPtr<UActorPool> _pool;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMeleeEnemy> _defaultMeleeEnemy;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARangedEnemy> _defaultRangedEnemy;

	UPROPERTY()
	TArray<TObjectPtr<ABaseEnemy>> _enemies;
	UPROPERTY()
	TArray<TObjectPtr<AEnemySpawnPoint>> _spawnPoints;

	FNextWave _nextWave;
	FOnComplete _completeDelegate;

	int _toSpawn;

	float _spawnTimer;
	float _spawnDelay;

	bool _isActive;
};
