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

	void Init(UEffectData* data, float lifeTime, float aoeSize, bool addPullEffect);
	void AddIgnoredActor(AActor* actor);
	void AddIgnoredActors(TArray<AActor*> actors);

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Populate();
	void ProcessEffects();

private:
	UPROPERTY()
	TObjectPtr<USphereComponent> _collider;
	UPROPERTY()
	TObjectPtr<UEffectData> _effect;
	UPROPERTY()
	TArray<TObjectPtr<AActor>> _ignore;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> _overlaps;

	float _aoeSize;

	float _lifeTime;
	float _lifeTimer;

	bool _pullActors;
};
