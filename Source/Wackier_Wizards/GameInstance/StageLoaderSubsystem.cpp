// Fill out your copyright notice in the Description page of Project Settings.


#include "StageLoaderSubsystem.h"
#include "../Level/StageData.h"
#include "Kismet/GameplayStatics.h"
#include "../Characters/Player/PlayerCharacter.h"
#include "../Gamemodes/StageGameMode.h"

void UStageLoaderSubsystem::LoadStage(int stage)
{
	if (_stageDataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Failed to load StageData")));
		return;
	}

	FString rowName = "Stage" + FString::FromInt(stage);

	static const FString ContextString(TEXT("Stage Context String"));
	FStageData* stageData = _stageDataTable->FindRow<FStageData>(FName(*rowName), ContextString, true);

	if (stageData != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Loaded %s"), *rowName));

		_currentStageData = stageData;
		UGameplayStatics::OpenLevel(GetWorld(), _currentStageData->levelName);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("Failed to load Stage%i"), stage));
	}
}

void UStageLoaderSubsystem::LoadDataTable()
{
	if (_stageDataTable != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("StageLoader has already loaded the StageDataTable"));
		return;
	}
	FSoftObjectPath path(TEXT("/Script/Engine.DataTable'/Game/1WWDEV/Ben-H/StageData/DT_StageData.DT_StageData'"));
	UObject* pathObject = path.ResolveObject();

	if (pathObject == nullptr)
	{
		pathObject = path.TryLoad();
	}

	if (pathObject != nullptr)
	{
		_stageDataTable = Cast<UDataTable>(pathObject);
		UE_LOG(LogTemp, Warning, TEXT("Stage Loader Succeeded"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Stage Loader Failed"));
	}
}

int UStageLoaderSubsystem::GetStageLevel()
{
	if (_currentStageData == nullptr)
	{
		return 0;
	}

	return _currentStageData->stage;
}

FStageData* UStageLoaderSubsystem::GetStageData()
{
	return _currentStageData;
}

TSubclassOf<AEnemySpawner> UStageLoaderSubsystem::GetSpawnerDefault()
{
	return _enemySpawner;
}

void UStageLoaderSubsystem::LoadHub()
{
	UGameplayStatics::OpenLevel(GetWorld(), _hubLevelName);
}

void UStageLoaderSubsystem::ResetStage()
{
	if (_currentStageData == nullptr)
	{
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), _currentStageData->levelName);
}

void UStageLoaderSubsystem::SetHubLevel(FName name)
{
	_hubLevelName = name;
}

void UStageLoaderSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UStageLoaderSubsystem::Deinitialize()
{

	Super::Deinitialize();
}

bool UStageLoaderSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(Outer))
	{
		return true;
	}

	return false;
}
