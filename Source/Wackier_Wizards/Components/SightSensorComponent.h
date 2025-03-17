// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SightSensorComponent.generated.h"

class UGOAP_Agent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API USightSensorComponent : public UActorComponent
{
	GENERATED_BODY()

//Sensor to determine if owner has line of sight on a target
public:	
	// Sets default values for this component's properties
	USightSensorComponent();

	void Init(TObjectPtr<UGOAP_Agent> agent);
	void SetTarget(TObjectPtr<AActor> target);

	bool Scan();

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
	UPROPERTY(EditAnywhere)
	float _scanInterval;
	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 2))
	float _fov;

	float _timer;
};
