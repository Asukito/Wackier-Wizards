// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "MeleeNPC.generated.h"

class AWWAIController;
class APlayerCharacter;

UCLASS()
class WACKIER_WIZARDS_API AMeleeNPC : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeNPC();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Attack(IDamageable* target);

private:
	UPROPERTY()
	TObjectPtr<AWWAIController> _controller;

	UPROPERTY()
	TWeakObjectPtr<APlayerCharacter> _player;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float _meleeRange;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int _meleeDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float _meleeDelay;
	float _timer;
};
