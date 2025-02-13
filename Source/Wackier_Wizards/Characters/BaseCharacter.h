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

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	bool TakeDamage(int amount, FString source) override;
	void Heal(int amount) override;
	void AdjustMaxHealth(int amount) override;
	void AdjustWalkSpeed(float percent);
	bool HasMovementComponent() override;
	void Kill() override;
	virtual void Respawn(bool isDead) override;
	void AddEffect(UEffectData* effect) override;

	//---- HELPERS ----
	IDamageable* GetDamageableAccess() override;
	IHealth* GetHealthAccess() override;
	const int GetHealth(bool getPercent) noexcept override;
	const int GetMaxHealth() noexcept override;
	bool HasEffect(FString effectName) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UHealthComponent> healthComponent;
	UPROPERTY()
	TObjectPtr<UEffectsComponent> effectComponent;

	float maxWalkSpeed;
	FVector spawnLocation;
};
