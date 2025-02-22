// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DistanceSensorComponent.generated.h"

class UGOAP_Agent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UDistanceSensorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDistanceSensorComponent();

	void Init(float distance, TObjectPtr<UGOAP_Agent> agent);

	void SetTarget(TObjectPtr<AActor> target);
	bool CheckDistanceToTarget();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TObjectPtr<AActor> _target;
	TObjectPtr<UGOAP_Agent> _agent;

	UPROPERTY(EditAnywhere)
	float _distance;
};
