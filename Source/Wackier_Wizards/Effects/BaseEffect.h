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

public:
	virtual void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list);
	virtual void Update(float deltaTime);
	virtual void EndEffect();
	void ClearEffect();
	
	FString GetEffectName();

protected:
	bool ProcessEffect();
	void ProcessEffectRemoval();

protected:
	IEffectable* owner;
	UPROPERTY()
	TObjectPtr<UEffectData> effectData;

	float timer;
	int duration;
	bool hasEnded = false;
private:
	FOnClear _clearDelegate;

};
