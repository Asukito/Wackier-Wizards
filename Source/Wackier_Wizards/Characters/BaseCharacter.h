// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Interfaces/Health.h"
#include "../Interfaces/Effectable.h"
#include "../Interfaces/Damageable.h"
#include "../Components/HealthComponent.h"
#include "../Components/EffectsComponent.h"
#include "BaseCharacter.generated.h"

UCLASS()
class WACKIER_WIZARDS_API ABaseCharacter : public ACharacter, public IEffectable, public IDamageable, public IHealth
{
	GENERATED_BODY()

//Base Character class that handles base logic for (current) character-related interfaces. 
public:
	// Sets default values for this character's properties
	ABaseCharacter();

	//---- IEFFECTABLE OVERRIDES ----
	IDamageable* GetDamageableAccess() override;
	IHealth* GetHealthAccess() override;
	void AdjustWalkSpeed(float percent);
	bool HasMovementComponent() override;
	void AddEffect(UEffectData* effect) override;
	bool HasEffect(FString effectName) override;
	UAuraEffect* GetAura() override;
	virtual void SetCanAct(bool val) override;

	//---- IDAMAGEABLE OVERRIDES ----
	void Kill() override;
	bool DealDamage(int amount, FString source) override;

	//---- IHEALTH OVERRIDES ----
	void Heal(int amount) override;
	void AdjustMaxHealth(int amount) override;
	const int GetHealth(bool getPercent) noexcept override;
	const int GetBaseHealth() noexcept override;
	const int GetMaxHealth() noexcept override;
	virtual void Respawn(bool isDead) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Binds any delegates if needed.
	virtual void BindDelegates();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UHealthComponent> healthComponent;
	UPROPERTY()
	TObjectPtr<UEffectsComponent> effectComponent;

	bool canAttack;

	float maxWalkSpeed;
	FVector spawnLocation;
};
