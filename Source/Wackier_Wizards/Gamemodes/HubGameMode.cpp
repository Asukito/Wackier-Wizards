// Fill out your copyright notice in the Description page of Project Settings.


#include "HubGameMode.h"
#include "../GameInstance/StageLoaderSubsystem.h"
#include "Kismet/GameplayStatics.h"

void AHubGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (TObjectPtr<UStageLoaderSubsystem> stageLoader = GetGameInstance()->GetSubsystem<UStageLoaderSubsystem>())
	{
		stageLoader->LoadDataTable();
		stageLoader->SetHubLevel(*UGameplayStatics::GetCurrentLevelName(GetWorld()));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Green, FString::Printf(TEXT("STAGE LOADER NULL")));
	}
}
