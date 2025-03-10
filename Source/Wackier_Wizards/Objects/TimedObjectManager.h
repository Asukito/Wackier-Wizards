// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimedObjectManager.generated.h"

class ATimedPillar;

UCLASS()
class WACKIER_WIZARDS_API ATimedObjectManager : public AActor
{
	GENERATED_BODY()

//Container for timed actors (such as pillars) and handles if they are active or inactive (needs rework/replacing).
public:	
	// Sets default values for this actor's properties
	ATimedObjectManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Init();
	void NextGroup();
	void UpdatePillars();
private:
	UPROPERTY(EditAnywhere)
	TMap<TObjectPtr<ATimedPillar>, int> _pillars;
	UPROPERTY(EditAnywhere)
	int _maxGroup;
	UPROPERTY(EditAnywhere)
	float _delayBetweenSwitch;

	int _index;
	float _timer;
	bool _hasInit;
};
