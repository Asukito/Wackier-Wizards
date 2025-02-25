// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraEffect.h"
#include "TickAuraEffect.generated.h"

class IEffectable;

UCLASS()
class WACKIER_WIZARDS_API UTickAuraEffect : public UAuraEffect
{
	GENERATED_BODY()
	
public:
	virtual void Update(float deltaTime) override;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
protected:
	virtual void HandleOverlap() override;

private:
	void QueueRemoval(IEffectable* target);
	void EmptyQueue();

private:
	TArray<TScriptInterface<IEffectable>> _queue;
};
