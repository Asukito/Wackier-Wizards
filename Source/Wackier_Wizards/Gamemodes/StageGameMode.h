// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StageGameMode.generated.h"

class UWaveManager;
class AEnemySpawner;

struct FStageData;

UCLASS()
class WACKIER_WIZARDS_API AStageGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	void InitWaves(FStageData* data);

private:
	UPROPERTY()
	TObjectPtr<UWaveManager> _waveManager;
};
