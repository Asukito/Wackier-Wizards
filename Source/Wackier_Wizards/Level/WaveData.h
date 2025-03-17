// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveData.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int meleeEnemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int rangedEnemies;
};