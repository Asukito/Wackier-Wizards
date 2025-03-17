// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAP_Belief.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_RetVal(bool, FEvaluate);
UCLASS()
class WACKIER_WIZARDS_API UGOAP_Belief : public UObject
{
	GENERATED_BODY()
	
//Class representing a belief. This represents a GOAP_Agent's view of the world it's within. This is used to determine the agent's goals and actions.
public:
	UGOAP_Belief();

	//Returns the result of the condition. True = complete, false = incomplete.
	bool Evaluate();
	FString GetName();

	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UGOAP_Belief> belief;

	public:
		Builder(FString name)
		{
			belief = NewObject<UGOAP_Belief>();
			belief->_name = name;
		}
		//Creates a conditional belief by binding a bool function to the belief.
		Builder WithCondition(TFunction<bool()> condition)
		{
			belief->_condition.BindLambda(condition);
			return *this;
		}
		//Beliefs can also have a location to be used as a condition. Currently not used.
		Builder WithLocation(FVector location)
		{
			belief->_location = location;
			return *this;
		}

		UGOAP_Belief* Build()
		{
			return belief.Get();
		}
	};

public:
	FString _name;
	FEvaluate _condition;
	FVector _location;
};
