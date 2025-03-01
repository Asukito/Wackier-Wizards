// Fill out your copyright notice in the Description page of Project Settings.


#include "StageGameMode.h"
#include "../Level/WaveManager.h"
#include "../GameInstance/StageLoaderSubsystem.h"

void AStageGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		InitWaves(stageLoader->GetStageData());
	}

}

void AStageGameMode::InitWaves(FStageData* data)
{
	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		_waveManager = NewObject<UWaveManager>();
		_waveManager->Init(GetWorld(), data, stageLoader->GetSpawnerDefault());
	}
}
