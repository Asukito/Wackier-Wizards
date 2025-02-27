// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseEnemy.h"
#include "MeleeEnemy.generated.h"

/**
 * 
 */
UCLASS()
class WACKIER_WIZARDS_API AMeleeEnemy : public ABaseEnemy
{
	GENERATED_BODY()
	
//Melee Enemy class. Melee enemies just seek the player when spawned, and attack when in range. 
public:
	AMeleeEnemy();

	virtual void Tick(float DeltaTime) override;
	void Attack(IDamageable* target);
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float _meleeRange;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float _meleeDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float _meleeDelay;

	float _timer;
};
