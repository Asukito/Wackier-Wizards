// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEffect.generated.h"

class IEffectable;
class UEffectsComponent;
class UEffectData;

DECLARE_DELEGATE_OneParam(FOnClear, UBaseEffect*);

UCLASS()
class WACKIER_WIZARDS_API UBaseEffect : public UObject
{
	GENERATED_BODY()

//Base Effect class that all effects inherit from
public:
	virtual void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list);
	virtual void Update(float deltaTime);
	virtual void EndEffect();
	//Queues the effect removal from the effect actor.
	void ClearEffect();
	
	FString GetEffectName();

protected:
	//Processes any stat-related effects
	bool ProcessEffect(IEffectable* effectable);
	//Reverses any stat-related effects
	void ProcessEffectRemoval(IEffectable* effectable);

	void HandleBonus();
protected:
	UPROPERTY()
	TScriptInterface<IEffectable> owner;
	UPROPERTY()
	TObjectPtr<UEffectData> effectData;

	float timer;
	int duration;
	bool hasEnded = false;

	FOnClear _clearDelegate;
};
