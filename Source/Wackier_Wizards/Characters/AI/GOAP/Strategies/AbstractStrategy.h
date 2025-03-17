// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AbstractStrategy.generated.h"

class UGOAP_Agent;

UCLASS(Abstract)
class WACKIER_WIZARDS_API UAbstractStrategy : public UObject
{
	GENERATED_BODY()
	
//Abstract class for Strategies to inherit from. 
public:
	//Checks if the action can be performed, currently not in use. Useful if preconditions can be affected after a plan is created, such as a neccessary item existing when the plan was created
	//being destroyed (currently not possible).
	virtual bool CanPerform();
	//Checks if the action is complete.
	virtual bool Complete();

	virtual void Start(UGOAP_Agent* agent);
	virtual void Update(float deltaTime);
	virtual void Stop();
};
