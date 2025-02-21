// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectsComponent.generated.h"

class UBaseEffect;
class UEffectData;
class AResultantEffectContainer;
class UAuraEffect;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UEffectsComponent : public UActorComponent
{
	GENERATED_BODY()

//Component to handle all effects applied to it's owner.
public:	
	// Sets default values for this component's properties
	UEffectsComponent();

	//Creates and adds the effect. Creation should be moved to a factory if anything outside of this component ever needs to create an effect.
	void CreateAndAddEffect(UEffectData* effectData);
	//Queues the removal of an effect. Instant removal can cause errors as the effects array will change size when being processed in update.
	void QueueRemoval(UBaseEffect* effect);
	//Queues the removal of all effects
	void ClearEffects();

	UAuraEffect* GetAura();

	//Check if an effect with the inputted name is contained within effects
	bool Contains(FString name);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	//Empties effects
	void RemoveEffects();
	//Check if an effect with the inputted name is contained within effects and then return it
	UBaseEffect* ReturnContains(FString name);
	//Check if an effect can interact with a contained effect
	UEffectData* CheckIfResultantValid(UEffectData* effectData);

private:
	UPROPERTY()
	TArray<TObjectPtr<UBaseEffect>> _effects;

	UPROPERTY()
	TArray<TObjectPtr<UBaseEffect>> _toRemove;

	TObjectPtr<AResultantEffectContainer> _resultantContainer;

	UPROPERTY()
	TObjectPtr<UAuraEffect> _aura;
};
