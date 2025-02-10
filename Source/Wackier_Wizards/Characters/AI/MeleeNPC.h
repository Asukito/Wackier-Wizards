// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interfaces/Effectable.h"
#include "../../Interfaces/Damageable.h"
#include "../../Interfaces/Health.h"
#include "MeleeNPC.generated.h"

class AWWAIController;
class APlayerCharacter;
class UEffectsComponent;
class UHealthComponent;

UCLASS()
class WACKIER_WIZARDS_API AMeleeNPC : public ACharacter, public IEffectable, public IDamageable, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMeleeNPC();

	void AddEffect(UEffectData* effect) override;
	IDamageable* GetDamageableAccess() override;
	IHealth* GetHealthAccess() override;
	bool HasEffect(FString effectName) override;
	void AdjustWalkSpeed(float percent) override;
	bool HasMovementComponent() override
	{
		return true;
	}
	bool TakeDamage(int amount, FString source) override;
	void Kill() override;

	void Heal(int amount) override;
	void AdjustMaxHealth(int amount) override;
	const int GetHealth(bool getPercent) noexcept override;
	const int GetMaxHealth() noexcept override;
	void Respawn(bool isDead) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void Attack(IDamageable* target);
private:
	FVector _spawnPoint;

	UPROPERTY()
	TObjectPtr<AWWAIController> _controller;

	UPROPERTY()
	TWeakObjectPtr<APlayerCharacter> _player;

	UPROPERTY()
	TObjectPtr<UEffectsComponent> _effectComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UHealthComponent> _healthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float _meleeRange;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	int _meleeDamage;
	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float _meleeDelay;
	float _timer;

	float _maxWalkSpeed;
};
