// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "StageLoaderSubsystem.generated.h"

struct FStageData;
class AEnemySpawner;

UCLASS(Blueprintable)
class WACKIER_WIZARDS_API UStageLoaderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void LoadStage(int stage);
	UFUNCTION(BlueprintCallable)
	void LoadDataTable();
	UFUNCTION(BlueprintCallable)
	void LoadHub();
	UFUNCTION(BlueprintCallable)
	void ResetStage();

	void SetHubLevel(FName name);

	int GetStageLevel();
	FStageData* GetStageData();
	TSubclassOf<AEnemySpawner> GetSpawnerDefault();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemySpawner> _enemySpawner;

	UPROPERTY(EditDefaultsOnly)
	FName _hubLevelName;

	UPROPERTY()
	TObjectPtr<UDataTable> _stageDataTable;

	FStageData* _currentStageData;
};
