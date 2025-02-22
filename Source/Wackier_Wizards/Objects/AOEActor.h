// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AOEActor.generated.h"

class UEffectData;
class USphereComponent;

UCLASS()
class WACKIER_WIZARDS_API AAOEActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAOEActor();

	void Init(UEffectData* data);
	void AddIgnoredActors(TArray<AActor*> actors);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void DoAoe();
private:
	UPROPERTY()
	TObjectPtr<USphereComponent> _collider;
	UPROPERTY()
	TObjectPtr<UEffectData> _effect;
	UPROPERTY()
	TArray<TObjectPtr<AActor>> _ignore;

	float _lifeTime;
	float _lifeTimer;

	float _overlapDelay;
	float _overlapTimer;
};
