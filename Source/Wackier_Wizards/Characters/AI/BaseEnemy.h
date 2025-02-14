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

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TWeakObjectPtr<APlayerCharacter> player;
private:
	UPROPERTY()
	TObjectPtr<USeekerComponent> _seeker;
	UPROPERTY()
	TObjectPtr<AWWAIController> _controller;

};
