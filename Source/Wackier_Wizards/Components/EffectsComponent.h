// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Effects/Effect.h"
#include "EffectsComponent.generated.h"

class UBaseEffect;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectsComponent();

	void CreateAndAddEffect(Effect effect);
	void AddEffect(UBaseEffect* effect);
	void QueueRemoval(UBaseEffect* effect);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void RemoveEffects();
private:
	UPROPERTY()
	TArray<TObjectPtr<UBaseEffect>> _effects;

	UPROPERTY()
	TArray<TObjectPtr<UBaseEffect>> _toRemove;
};
