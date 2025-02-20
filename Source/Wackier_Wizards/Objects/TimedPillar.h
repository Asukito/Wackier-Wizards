// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimedPillar.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class WACKIER_WIZARDS_API ATimedPillar : public AActor
{
	GENERATED_BODY()

//Pillar that periodically rises and closes (needs rework/replacing).
public:	
	// Sets default values for this actor's properties
	ATimedPillar();

	void SetIsActive(bool val);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> _collider;

	bool _updateScale;
	bool _isActive;

	float _startZ;
};
