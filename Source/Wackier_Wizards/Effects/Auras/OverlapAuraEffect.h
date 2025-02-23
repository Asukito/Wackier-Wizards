// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraEffect.h"
#include "OverlapAuraEffect.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UOverlapAuraEffect : public UAuraEffect
{
	GENERATED_BODY()
	
public:
	virtual void EndEffect() override;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

protected:
	virtual void HandleOverlap() override;
};
