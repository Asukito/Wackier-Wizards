// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP_Agent.h"
#include "GOAPIncludes.h"
#include "Strategies/StrategyIncludes.h"

// Sets default values for this component's properties
UGOAP_Agent::UGOAP_Agent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UGOAP_Agent::Init()
{
	//_owner = Cast<ANPC_Base>(GetOwner());
}

#pragma region "GOAP"
void UGOAP_Agent::SetupBeliefs()
{
	UGOAP_BeliefFactory* factory = NewObject<UGOAP_BeliefFactory>();
	factory->Init(&_beliefs);
}

void UGOAP_Agent::SetupActions()
{
}

void UGOAP_Agent::SetupGoals()
{
}

void UGOAP_Agent::CalculateActionPlan()
{
	int priorityLevel = (_currentGoal != nullptr) ? _currentGoal->_priority : 0;

	TArray<UGOAP_Goal*> goalsToCheck;

	if (_currentGoal != nullptr)
	{
		goalsToCheck = _goals.FilterByPredicate([&](const UGOAP_Goal* index) { return index->_priority > priorityLevel; });
	}
	else
	{
		goalsToCheck = _goals;
	}

	UGOAP_Plan* potentialPlan = _planner->Plan(this, _goals, nullptr);

	if (potentialPlan != nullptr)
	{
		_plan = potentialPlan;
	}
}

void UGOAP_Agent::Reset()
{
	_goals.Empty();
	_beliefs.Empty();
	_actions.Empty();

	_planner = nullptr;

	SetupBeliefs();
	SetupActions();
	SetupGoals();

	_planner = NewObject<UGOAP_Planner>();
}

TMap<FString, TObjectPtr<UGOAP_Belief>> UGOAP_Agent::GetBeliefs() const
{
	return _beliefs;
}

TArray<TObjectPtr<UGOAP_Action>> UGOAP_Agent::GetActions() const
{
	return _actions;
}

TArray<TObjectPtr<UGOAP_Goal>> UGOAP_Agent::GetGoals() const
{
	return _goals;
}
#pragma endregion

#pragma region "AI"
void UGOAP_Agent::SetPauseAgent(bool val)
{
	if (_isPaused == val)
	{
		return;
	}

	_isPaused = val;

	//_owner->SetPauseMovement(_isPaused);
}

void UGOAP_Agent::TogglePauseAgent()
{
	SetPauseAgent(!_isPaused);
}

void UGOAP_Agent::SetDestination(FVector destination)
{
	//_owner->SetDestination(destination);
}
#pragma endregion

#pragma region "Helpers"
USkeletalMeshComponent* UGOAP_Agent::GetMesh()
{
	return nullptr;// _owner->GetMesh();
}

FVector UGOAP_Agent::GetCurrentDestination() const
{
	return FVector::ZeroVector;// _owner->GetCurrentDestination();
}

FVector UGOAP_Agent::GetActorLocation() const
{
	return GetCurrentDestination();// _owner->GetActorLocation();
}

FVector UGOAP_Agent::GetForwardVector() const
{
	return GetActorLocation();// _owner->GetActorForwardVector();;
}


bool UGOAP_Agent::HasPath() const
{
	return false; //_owner->HasPath();
}
#pragma endregion

// Called when the game starts
void UGOAP_Agent::BeginPlay()
{
	Super::BeginPlay();

	SetupBeliefs();
	SetupActions();
	SetupGoals();

	_planner = NewObject<UGOAP_Planner>();
}


// Called every frame
void UGOAP_Agent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	_timer += DeltaTime * 0.25f;

	if (_timer >= 24)
	{
		_timer = 0;
	}

	if (_isPaused == true)
	{
		return;
	}

	if (_currentAction == nullptr)
	{
		CalculateActionPlan();

		if (_plan != nullptr && _plan->actions.Num() > 0)
		{
			_currentGoal = _plan->goal;
			_currentAction = _plan->actions.Pop();

			_currentAction->Start(this);
		}
	}

	if (_plan != nullptr && _currentAction != nullptr)
	{
		_currentAction->Update(DeltaTime);

		if (_currentAction->IsComplete() == true)
		{
			_currentAction->Stop();
			_currentAction = nullptr;

			if (_plan->actions.Num() == 0)
			{
				_lastGoal = _currentGoal;
				_currentGoal = nullptr;
			}
			else
			{
				_currentAction = _plan->actions.Pop();
				_currentAction->Start(this);
			}
		}
	}

	if (_currentAction == nullptr)
	{
		_planFailCounter += 1;

		if (_planFailCounter > 5)
		{
			Reset();
		}
	}
	else
	{
		_planFailCounter = 0;
	}
}

