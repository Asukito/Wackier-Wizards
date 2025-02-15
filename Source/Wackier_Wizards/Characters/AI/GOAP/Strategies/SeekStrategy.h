// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbstractStrategy.h"
#include "SeekStrategy.generated.h"

class UGOAP_Agent;

UCLASS()
class WACKIER_WIZARDS_API USeekStrategy : public UAbstractStrategy
{
	GENERATED_BODY()
	
public:
	virtual void Start(UGOAP_Agent* agent) override;
	virtual void Update(float deltaTime) override;
	virtual void Stop() override;

	virtual bool Complete() override;

private:
	UPROPERTY()
	TWeakObjectPtr<UGOAP_Agent> _agent;
};
