// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"
#include "Kismet/GameplayStatics.h"
#include "../Characters/Player/PlayerCharacter.h"

// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AEnemySpawnPoint::IsActive()
{
	return _isActive;
}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	if (TObjectPtr<APlayerCharacter> player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		_player = player;
	}

	_spawnTimer = _spawnCooldown;
}

bool AEnemySpawnPoint::CheckIfActive()
{
	if (_spawnTimer > 0 || _player == nullptr)
	{
		return false;
	}

	FVector playerPos = _player->GetActorLocation();

	FVector spawnPos = GetActorLocation();

	FVector distance = playerPos - spawnPos;

	float zCheck = playerPos.Z - spawnPos.Z;

	if (zCheck > _maxZClamp || zCheck < -_maxZClamp)
	{
		return false;
	}

	if (_minDistance < distance.Size() && distance.Size() < _maxDistance)
	{
		return true;
	}

	return false;
}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	_spawnTimer -= DeltaTime;
	_isActive = CheckIfActive();
}

