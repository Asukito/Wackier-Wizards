// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAP_Plan.generated.h"

class UGOAP_Goal;
class UGOAP_Action;

UCLASS()
class WACKIER_WIZARDS_API UGOAP_Plan : public UObject
{
	GENERATED_BODY()

//Class that contains actions contained within a plan. Also stores the total plan cost that can be used to compare plans in future (if necessary).
public:
	UGOAP_Plan();

	void Init(UGOAP_Goal* planGoal, TArray<UGOAP_Action*> planActions, int planCost);
public:
	TObjectPtr<UGOAP_Goal> goal;
	TArray<TObjectPtr<UGOAP_Action>> actions;
	int cost;
};
