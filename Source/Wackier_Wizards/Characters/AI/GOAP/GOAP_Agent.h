// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GOAP_Agent.generated.h"

class UGOAP_Belief;
class UGOAP_Goal;
class UGOAP_Planner;
class UGOAP_Action;
class UGOAP_Plan;
class UDistanceSensorComponent;
class UTargetSensorComponent;
class USightSensorComponent;
class ARangedEnemy;
class APlayerCharacter;
class USpellBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UGOAP_Agent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGOAP_Agent();

	void ConstructorInit();
	void Init();

	//---- GOAP ----
	TMap<FString, TObjectPtr<UGOAP_Belief>> GetBeliefs() const;
	TArray<TObjectPtr<UGOAP_Action>> GetActions() const;
	TArray<TObjectPtr<UGOAP_Goal>> GetGoals() const;

	//---- AI ----
	void SetPauseAgent(bool val);
	void TogglePauseAgent();
	void SetDestination(FVector destination);
	void SetHasLineOfSight(bool val);
	void SetIsTargetInRange(bool val);
	void SetIsTargetTooClose(bool val);
	void SetSeekPlayer(bool val);
	void Attack();
	void SetPlayer(APlayerCharacter* player);

	//---- HELPERS ----
	FVector GetCurrentDestination() const;
	FVector GetActorLocation() const;
	FVector GetForwardVector() const;
	bool HasLineOfSight() const;
	bool TargetIsInRange() const;
	bool TargetIsTooClose() const;
	bool HasPath() const;
	APlayerCharacter* GetPlayer() const;
	AActor* GetPlayerActor() const;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//---- GOAP ----
	void SetupBeliefs();
	void SetupActions();	
	void SetupGoals();
	void CalculateActionPlan();
	void Reset();

private:
	//---- GOAP ----
	UPROPERTY()
	TMap<FString, TObjectPtr<UGOAP_Belief>> _beliefs;
	UPROPERTY()
	TArray<TObjectPtr<UGOAP_Action>> _actions;
	UPROPERTY()
	TArray<TObjectPtr<UGOAP_Goal>> _goals;
	UPROPERTY()
	TObjectPtr<UGOAP_Planner> _planner;
	UPROPERTY()
	TObjectPtr<UGOAP_Plan> _plan;
	UPROPERTY()
	TObjectPtr<UGOAP_Action> _currentAction;
	UPROPERTY()
	TObjectPtr<UGOAP_Goal> _currentGoal;
	UPROPERTY()
	TObjectPtr<UGOAP_Goal> _lastGoal;

	UPROPERTY()
	TObjectPtr<ARangedEnemy> _owner;
	UPROPERTY()
	TObjectPtr<APlayerCharacter> _player;
	UPROPERTY()
	TObjectPtr<USpellBase> _spell;
	float _spellRange;

	int _planFailCounter;
	bool _isPaused;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDistanceSensorComponent> _distanceSensor;
	UPROPERTY(EditDefaultsOnly)
	float _preferredDistance;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTargetSensorComponent> _targetSensor;
	UPROPERTY(EditDefaultsOnly)
	float _tooCloseRange;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USightSensorComponent> _sightSensor;

	bool _hasLineOfSight;
	bool _isTargetInRange;
	bool _isTargetTooClose;
};
