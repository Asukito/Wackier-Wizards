// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEffect.h"
#include "AuraEffect.generated.h"

class USphereComponent;
class IEffectable;
class UNiagaraComponent;

UCLASS()
class WACKIER_WIZARDS_API UAuraEffect : public UBaseEffect
{
	GENERATED_BODY()

public:
	virtual void StartEffect(UEffectData* data, AActor* actor, UEffectsComponent* list) override;
	virtual void Update(float deltaTime) override;
	virtual void EndEffect() override;

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	void SetUpAura(AActor* actor);
	virtual void HandleOverlap();

protected:
	UPROPERTY()
	TObjectPtr<USphereComponent> aura;

	UPROPERTY()
	TArray<TScriptInterface<IEffectable>> overlaps;

	UPROPERTY()
	TObjectPtr<UNiagaraComponent> niagara;
};
