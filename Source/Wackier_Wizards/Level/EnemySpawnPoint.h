// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

class APlayerCharacter;

UCLASS()
class WACKIER_WIZARDS_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

	bool IsActive();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool CheckIfActive();

private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> _player;

	UPROPERTY(EditDefaultsOnly)
	float _minDistance;
	UPROPERTY(EditDefaultsOnly)
	float _maxDistance;
	UPROPERTY(EditDefaultsOnly)
	float _maxZClamp;

	UPROPERTY(EditDefaultsOnly)
	float _spawnCooldown;
	float _spawnTimer;

	bool _isActive;
};
