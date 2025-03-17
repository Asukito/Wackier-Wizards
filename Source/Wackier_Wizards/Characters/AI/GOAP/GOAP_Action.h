// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAP_Action.generated.h"

class UGOAP_Belief;
class UAbstractStrategy;
class UGOAP_Agent;

UCLASS()
class WACKIER_WIZARDS_API UGOAP_Action : public UObject
{
	GENERATED_BODY()
	
//Class representing an action. An action contains the logic (a Strategy) to be performed when this action is being worked on. 
//Actions can have preconditions necessary to start this action. Effects that the action will lead to. A cost that effects planning. 
public:
	UGOAP_Action();

	void Start(UGOAP_Agent* agent);
	void Update(float deltaTime); 
	void Stop();

	bool IsComplete();

	class WACKIER_WIZARDS_API Builder
	{
		TWeakObjectPtr<UGOAP_Action> action;

	public:

		Builder(FString name)
		{
			action = NewObject<UGOAP_Action>();
			action->_name = name;
		}
		Builder WithCost(int cost)
		{
			action->_cost = cost;
			return *this;
		}
		Builder WithStrategy(UAbstractStrategy* strategy)
		{
			action->_strategy = strategy;
			return *this;
		}
		Builder AddPrecondition(UGOAP_Belief* precondition)
		{
			action->_preconditions.Add(precondition);
			return *this;
		}
		Builder AddEffect(UGOAP_Belief* effect)
		{
			action->_effects.Add(effect);
			return *this; 
		}
		UGOAP_Action* Build()
		{
			return action.Get();
		}
	};
public:
	UPROPERTY()
	TObjectPtr<UAbstractStrategy> _strategy;

	TArray<TObjectPtr<UGOAP_Belief>> _preconditions;
	TArray<TObjectPtr<UGOAP_Belief>> _effects;

	FString _name;
	int _cost;
};
