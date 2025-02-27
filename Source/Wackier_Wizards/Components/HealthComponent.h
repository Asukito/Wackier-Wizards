// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WACKIER_WIZARDS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

//A componet that handles an actors health
public:	
	// Sets default values for this component's properties
	UHealthComponent();

	//Adjust health based on a flat value
	void AdjustHealth(float amount);
	//Adjust health based on a percentage of the max health
	void AdjustHealthPercentage(float percentage);
	//Sets the health to the amount
	void SetHealth(float amount);
	void AdjustMaxHealth(int amount);
	//Return health 
	int GetHealth() const;
	//Return health as a percentage of the max health
	int GetHealthPercent() const;
	int GetBaseHealth() const;
	int GetMaxHealth() const;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	float _baseHealth;
	float _maxHealth;
	float _health;
};
