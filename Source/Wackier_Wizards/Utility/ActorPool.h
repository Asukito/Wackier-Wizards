// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActorPool.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API UActorPool : public UObject
{
	GENERATED_BODY()
	
public:
	void Init(UWorld* worldContext, TSubclassOf<AActor> toPool, int amount);
	void Populate(TArray<TObjectPtr<AActor>> pool);

	void ShufflePool(int iterations);
	void Empty();
	void Release();

	void ReturnPoolActor(AActor* toReturn);
	AActor* GetPoolActor(bool createNewIfEmpty, UWorld* worldContext);
	AActor* GetPoolActorOfType(UClass* type);
private:
	UPROPERTY()
	TSubclassOf<AActor> _default;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> _pool;
};
