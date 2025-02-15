// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAP_Agent.h"
#include "GOAPIncludes.h"
#include "Strategies/StrategyIncludes.h"
#include "../../../Characters/AI/RangedEnemy.h"
#include "../../../Characters/Player/PlayerCharacter.h"
#include "../../../Components/DistanceSensorComponent.h"
#include "../../../Components/TargetSensorComponent.h"
#include "../../../Components/SightSensorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../../Spells/SpellBase.h"

// Sets default values for this component's properties
UGOAP_Agent::UGOAP_Agent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_isPaused = true;

	_targetSensor = CreateDefaultSubobject<UTargetSensorComponent>(TEXT("Target Sensor"));
	checkf(_targetSensor, TEXT("GOAP_Agent TargetSensor failed to initialise"));

	_sightSensor = CreateDefaultSubobject<USightSensorComponent>(TEXT("Sight Sensor"));
	checkf(_sightSensor, TEXT("GOAP_Agent SightSensor failed to initialise"));

	_distanceSensor = CreateDefaultSubobject<UDistanceSensorComponent>(TEXT("Distance Sensor"));
	checkf(_distanceSensor, TEXT("GOAP_Agent DistanceSensor failed to initialise"));
}

void UGOAP_Agent::ConstructorInit()
{

}

void UGOAP_Agent::Init()
{
	_owner = Cast<ARangedEnemy>(GetOwner());

	_targetSensor->Init(_tooCloseRange, this);
	_targetSensor->AttachTo(_owner->GetRootComponent());

	_sightSensor->Init(this);
	_distanceSensor->Init(_preferredDistance, this);

	SetupBeliefs();
	SetupActions();
	SetupGoals();

	_planner = NewObject<UGOAP_Planner>();

	_spell = _owner->GetSpell();

	if (_spell != nullptr)
	{
		_spellRange = _spell->GetSpellRange();
	}
}

#pragma region "GOAP"
void UGOAP_Agent::SetupBeliefs()
{
	TObjectPtr<UGOAP_BeliefFactory> factory = NewObject<UGOAP_BeliefFactory>();
	factory->Init(&_beliefs);

	factory->AddBelief(TEXT("NO_LOS"), [this] { return !_hasLineOfSight; });
	factory->AddBelief(TEXT("HAS_LOS"), [this] { return _hasLineOfSight; });
	factory->AddBelief(TEXT("TARGET_NOT_IN_RANGE"), [this] { return !_isTargetInRange; });
	factory->AddBelief(TEXT("TARGET_IN_RANGE"), [this] { return _isTargetInRange; });
	factory->AddBelief(TEXT("TARGET_TOO_CLOSE"), [this] { return _isTargetTooClose; });
	factory->AddBelief(TEXT("ATTACKING"), [] { return false; });

	factory->MarkAsGarbage();
}

void UGOAP_Agent::SetupActions()
{
	_actions.Add(UGOAP_Action::Builder(TEXT("SEEK")).WithStrategy(NewObject<USeekStrategy>()).AddPrecondition(_beliefs.FindChecked(TEXT("NO_LOS"))).AddEffect(_beliefs.FindChecked(TEXT("HAS_LOS"))).Build());
	_actions.Add(UGOAP_Action::Builder(TEXT("CHASE")).WithStrategy(NewObject<UChaseStrategy>()).AddPrecondition(_beliefs.FindChecked(TEXT("HAS_LOS"))).AddPrecondition(_beliefs.FindChecked(TEXT("TARGET_NOT_IN_RANGE"))).AddEffect(_beliefs.FindChecked(TEXT("TARGET_IN_RANGE"))).Build());
	_actions.Add(UGOAP_Action::Builder(TEXT("ATTACK")).WithStrategy(NewObject<UAttackStrategy>()).AddPrecondition(_beliefs.FindChecked(TEXT("TARGET_IN_RANGE"))).AddEffect(_beliefs.FindChecked(TEXT("ATTACKING"))).Build());
}

void UGOAP_Agent::SetupGoals()
{
	_goals.Add(UGOAP_Goal::Builder(TEXT("SEEK")).WithPriority(1).AddDesiredEffect(_beliefs.FindChecked(TEXT("HAS_LOS"))).Build());
	_goals.Add(UGOAP_Goal::Builder(TEXT("ATTACK")).WithPriority(3).AddDesiredEffect(_beliefs.FindChecked(TEXT("ATTACKING"))).Build());
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
void UGOAP_Agent::SetHasLineOfSight(bool val)
{
	_hasLineOfSight = val;
}
void UGOAP_Agent::SetIsTargetInRange(bool val)
{
	_isTargetInRange = val;
}
void UGOAP_Agent::SetIsTargetTooClose(bool val)
{
	_isTargetTooClose = val;
}
void UGOAP_Agent::SetSeekPlayer(bool val)
{
	if (val == true)
	{
		_owner->SetSeekTarget(_player.Get());
		return;
	}

	_owner->ClearSeekTarget();
}
void UGOAP_Agent::Attack()
{
	if (_spell == nullptr)
	{
		return;
	}

	FVector distance = _player->GetActorLocation() = _owner->GetActorLocation();

	if (distance.Length() <= _spellRange)
	{
		_owner->CastSpell();
	}
}
void UGOAP_Agent::SetPlayer(APlayerCharacter* player)
{
	_player = player;

	if (_player == nullptr)
	{
		return;
	}

	_targetSensor->SetTarget(_player);
	_sightSensor->SetTarget(_player);
	_distanceSensor->SetTarget(_player);

	_isPaused = false;
}
#pragma endregion

#pragma region "Helpers"
FVector UGOAP_Agent::GetCurrentDestination() const
{
	return FVector::ZeroVector;// _owner->GetCurrentDestination();
}

FVector UGOAP_Agent::GetActorLocation() const
{
	return _owner->GetActorLocation();
}

FVector UGOAP_Agent::GetForwardVector() const
{
	return _owner->GetActorForwardVector();;
}

bool UGOAP_Agent::HasLineOfSight() const
{
	return _hasLineOfSight;
}

bool UGOAP_Agent::TargetIsInRange() const
{
	return _isTargetInRange;
}

bool UGOAP_Agent::TargetIsTooClose() const
{
	return _isTargetTooClose;
}

bool UGOAP_Agent::HasPath() const
{
	return _owner->HasPath();
}
APlayerCharacter* UGOAP_Agent::GetPlayer() const
{
	return _player;
}
AActor* UGOAP_Agent::GetPlayerActor() const
{
	return _player;
}
#pragma endregion

// Called when the game starts
void UGOAP_Agent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UGOAP_Agent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_isPaused == true)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Cyan, FString::Printf(TEXT("%s"), _currentAction ? *_currentAction->_name : TEXT("NO ACTION")));

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

