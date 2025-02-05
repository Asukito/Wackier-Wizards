// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseEffect.generated.h"

class IEffectable;
class UEffectsComponent;

DECLARE_DELEGATE_OneParam(FOnClear, UBaseEffect*);

UCLASS()
class WACKIER_WIZARDS_API UBaseEffect : public UObject
{
	GENERATED_BODY()

public:
	virtual void StartEffect(AActor* actor, UEffectsComponent* list);
	virtual void Update(float deltaTime);
	virtual void EndEffect();
	void ClearEffect();
	
protected:
	IEffectable* owner;

	float timer;
	int duration;
private:
	FOnClear _clearDelegate;
};
