// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WWAIController.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API AWWAIController : public AAIController
{
	GENERATED_BODY()
	
//Controller, for AI, that contains helper functions for managing movement and destinations.
public:
	UFUNCTION(BlueprintCallable)
	void SetDestination(const FVector destination);
	UFUNCTION(BlueprintCallable)
	void ClearDestination();
	UFUNCTION(BlueprintCallable)
	FVector GetCurrentDestination() const;

	//Pauses movement without clearing the current path
	UFUNCTION(BlueprintCallable)
	void SetPauseMovement(bool val);

	UFUNCTION(BlueprintCallable)
	bool HasPath() const;

private:
	FVector _currentDestination;
};
