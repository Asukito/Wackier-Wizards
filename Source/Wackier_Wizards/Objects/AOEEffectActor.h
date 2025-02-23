// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AOEEffectActor.generated.h"

class UEffectData;
class USphereComponent;

UCLASS()
class WACKIER_WIZARDS_API AAOEEffectActor : public AActor
{
	GENERATED_BODY()
	
//Actor that places an effect on IEffectables that enter it's radius.
public:	
	// Sets default values for this actor's properties
	AAOEEffectActor();

	void Init(UEffectData* data, float lifeTime, float aoeSize, float overlapDelay);
	void AddIgnoredActor(AActor* actor);
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

	float _aoeSize;

	float _lifeTime;
	float _lifeTimer;

	float _overlapDelay;
	float _overlapTimer;
};
