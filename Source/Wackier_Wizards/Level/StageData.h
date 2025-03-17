// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveData.h"
#include "StageData.generated.h"

USTRUCT(BlueprintType)
struct FStageData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int stage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName levelName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWaveData> waveData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isComplete;
};

