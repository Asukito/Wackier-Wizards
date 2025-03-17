// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WaveManager.generated.h"

struct FStageData;
struct FWaveData;
class AEnemySpawner;

UCLASS()
class WACKIER_WIZARDS_API UWaveManager : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(UWorld* world, FStageData* data, TSubclassOf<AEnemySpawner> spawnerDefault);
	FWaveData* GetNextWave();

private:
	UPROPERTY()
	TObjectPtr<AEnemySpawner> _spawner;

	FStageData* _stageData;
	int _currentWave;
};
