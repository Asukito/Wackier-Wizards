// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveData.h"
#include "StageData.generated.h"

USTRUCT(BlueprintType)
struct FStageData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int stage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName levelName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWaveData> waveData;
};

USTRUCT(BlueprintType)
struct FSpellTableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int spellID;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName spellName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString spellDescription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpellData> spellData;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture> spellIcon;
};