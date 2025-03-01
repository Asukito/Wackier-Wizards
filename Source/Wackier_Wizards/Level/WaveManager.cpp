// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"
#include "EnemySpawner.h"
#include "../Level/StageData.h"
#include "../GameInstance/StageLoaderSubsystem.h"

void UWaveManager::Init(UWorld* world, FStageData* data, TSubclassOf<AEnemySpawner> spawnerDefault)
{
	_stageData = data;
	
	if (_stageData == nullptr || spawnerDefault == nullptr)
	{
		return;
	}

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_spawner = world->SpawnActor<AEnemySpawner>(spawnerDefault, FVector::Zero(), FRotator::ZeroRotator, params);

	if (_spawner == nullptr)
	{
		return;
	}

	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = world->GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		_spawner->InitSpawner(world, [this]() { return GetNextWave(); }, [stageLoader]() { stageLoader->LoadHub(); });
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("WAVE INITIALISED")));
	}

}

FWaveData* UWaveManager::GetNextWave()
{
	if (_stageData == nullptr || _currentWave < 0 || _currentWave + 1 > _stageData->waveData.Num())
	{
		return nullptr;
	}

	_currentWave += 1;

	return &_stageData->waveData[_currentWave - 1];
}
