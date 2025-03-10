// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SeekerComponent.generated.h"

class AWWAIController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API USeekerComponent : public UActorComponent
{
	GENERATED_BODY()

//A component that sets the owner to seek a target
public:	
	// Sets default values for this component's properties
	USeekerComponent();

	void SetSeekTarget(AActor* target);
	void ClearSeekTarget();
	void SetController(AWWAIController* controller);
	void SetIsActive(bool isActive);
	void SetToRetreat(bool val);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	TObjectPtr<AActor> _target;
	UPROPERTY()
	TWeakObjectPtr<AWWAIController> _controller;

	bool _toRetreat;
	bool _isActive;
};
