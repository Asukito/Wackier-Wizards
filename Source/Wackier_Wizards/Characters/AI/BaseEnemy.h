// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "BaseEnemy.generated.h"

class AWWAIController;
class APlayerCharacter;
class USeekerComponent;
class UBoxComponent;

UCLASS()
class WACKIER_WIZARDS_API ABaseEnemy : public ABaseCharacter
{
	GENERATED_BODY()

//Base class for all enemies. Contains logic that interacts with the AI unique controller. Also contains a reference to the player and a SeekerComponent
public:
	// Sets default values for this character's properties
	ABaseEnemy();

	//---- SEEKERCOMPONENT FUNCTIONS ----
	void SetSeekTarget(AActor* target);
	void ClearSeekTarget();

	//---- AICONTROLLER FUNCTIONS ----
	void SetDestination(FVector destination);
	void ClearDestination();
	void SetFocus(AActor* target);
	void ClearFocus();
	bool HasPath();
	const FVector GetCurrentDestination();

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

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> _sightCollider;
};
