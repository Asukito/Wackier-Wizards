// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAP_BeliefFactory.generated.h"

class UGOAP_Belief;

UCLASS()
class WACKIER_WIZARDS_API UGOAP_BeliefFactory : public UObject
{
	GENERATED_BODY()
	
//A factory class that contains and populates a list of beliefs created within a GOAP_Agent.
public:
	UGOAP_BeliefFactory();

	void Init(TMap<FString, TObjectPtr<UGOAP_Belief>>* beliefs);
	void AddBelief(FString name, TFunction<bool()> condition);
	void AddLocationBelief(FString name, FVector location);

private:
	TMap<FString, TObjectPtr<UGOAP_Belief>>* _beliefs;
};
