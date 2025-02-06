// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectsComponent.generated.h"

class UBaseEffect;
class UEffectData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEffectsComponent();

	void CreateAndAddEffect(UEffectData* effectData);
	void QueueRemoval(UBaseEffect* effect);

	bool Contains(FString name);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void RemoveEffects();
	UBaseEffect* ReturnContains(FString name);

private:
	UPROPERTY()
	TArray<TObjectPtr<UBaseEffect>> _effects;

	UPROPERTY()
	TArray<TObjectPtr<UBaseEffect>> _toRemove;
};
