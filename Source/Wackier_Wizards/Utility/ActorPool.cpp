// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

void UActorPool::Init(UWorld* worldContext, TSubclassOf<AActor> toPool, int amount)
{
	if (worldContext == nullptr || toPool == nullptr || amount == 0)
	{
		return;
	}

	_default = toPool;

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	params.bNoFail = true;

	for (int i = 0; i < amount; i++)
	{
		TObjectPtr<AActor> newActor = worldContext->SpawnActor<AActor>(_default, FVector::ZeroVector, FRotator::ZeroRotator, params);

		if (newActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to pool actor"));
			continue;
		}

		_pool.Add(newActor);
		newActor->SetActorHiddenInGame(true);
		newActor->SetActorEnableCollision(false);
	}

	if (_pool.Num() != amount)
	{
		UE_LOG(LogTemp, Error, TEXT("Pool count does not equal requested amount"));
	}
}

void UActorPool::Populate(TArray<TObjectPtr<AActor>> pool)
{
	if (pool.Num() == 0)
	{
		return;
	}

	for (TObjectPtr<AActor> actor : pool)
	{
		if (actor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Tried to pool null enemy"));
			continue;
		}

		actor->SetActorHiddenInGame(true);
		actor->SetActorEnableCollision(false);
	}

	_pool = pool;
}

void UActorPool::ShufflePool(int iterations = 1)
{
	if (_pool.Num() <= 1)
	{
		return;
	}

	for (int i = 0; i < iterations; i++)
	{
		_pool.Sort([](const AActor& Item1, const AActor& Item2) { return FMath::FRand() < 0.5f; });
	}
}

void UActorPool::Empty()
{
	if (_pool.Num() == 0)
	{
		return;
	}

	for (TObjectPtr<AActor> actor : _pool)
	{
		actor->Destroy();
	}

	_pool.Empty();
}

void UActorPool::Release()
{
	_default = nullptr;
	Empty();
	MarkAsGarbage();
}

void UActorPool::ReturnPoolActor(AActor* toReturn)
{
	if (_pool.Contains(toReturn) == true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Red, FString::Printf(TEXT("TRIED TO RETURN ALREADY POOLED ACTOR")));
		return;
	}

	toReturn->SetActorHiddenInGame(true);
	toReturn->SetActorEnableCollision(false);
	_pool.Push(toReturn);
}

AActor* UActorPool::GetPoolActor(bool createNewIfEmpty, UWorld* worldContext = nullptr)
{
	TObjectPtr<AActor> toReturn = nullptr;

	if (_pool.Num() != 0)
	{
		toReturn = _pool.Pop(true);
		toReturn->SetActorHiddenInGame(false);
		toReturn->SetActorEnableCollision(true);

		return toReturn;
	}

	if (createNewIfEmpty == false || worldContext == nullptr || _default == nullptr)
	{
		return toReturn;
	}

	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	params.bNoFail = true;
	toReturn = worldContext->SpawnActor<AActor>(_default, FVector::ZeroVector, FRotator::ZeroRotator, params);

	return toReturn;
}

AActor* UActorPool::GetPoolActorOfType(UClass* type)
{
	if (_pool.Num() == 0 || type == nullptr)
	{
		return nullptr;
	}

	for (TObjectPtr<AActor> actor : _pool)
	{
		if (actor->IsA(type) == true)
		{
			return actor;
		}
	}

	return nullptr;
}
