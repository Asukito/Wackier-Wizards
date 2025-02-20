// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetSensorComponent.generated.h"

class USphereComponent;
class UGOAP_Agent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UTargetSensorComponent : public UActorComponent
{
	GENERATED_BODY()

//Sensor that checks if a target is in a set range from the owner.
public:	
	// Sets default values for this component's properties
	UTargetSensorComponent();

	void Init(float radius, TObjectPtr<UGOAP_Agent> agent);
	void SetTarget(TObjectPtr<AActor> target);
	//Handles component attachment to this components owner 
	void AttachTo(USceneComponent* component);

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> _sensor;

	TObjectPtr<AActor> _target;
	TObjectPtr<UGOAP_Agent> _agent;
	float _radius;
};
