// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "BaseEnemy.generated.h"

class AWWAIController;
class APlayerCharacter;
class USeekerComponent;

UCLASS()
class WACKIER_WIZARDS_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();
	void SetSeekTarget(AActor* target);
	void ClearSeekTarget();
	void SetDestination(FVector destination);
	void ClearDestination();

	bool HasPath();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> player;

private:
	UPROPERTY()
	TObjectPtr<AWWAIController> _controller;
	UPROPERTY()
	TObjectPtr<USeekerComponent> _seeker;
};
