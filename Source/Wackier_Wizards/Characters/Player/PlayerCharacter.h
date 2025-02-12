// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interfaces/Effectable.h"
#include "../../Interfaces/Damageable.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Interfaces/Health.h"
#include "../../Spells/SpellType.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class AWWPlayerController;
class UStaticMeshComponent;
class UHealthComponent;
class USpellData;
class USpellBase;
class UEffectsComponent;

UCLASS()
class WACKIER_WIZARDS_API APlayerCharacter : public ACharacter, public IEffectable, public IDamageable, public ISpellCaster, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void SetController(AWWPlayerController* controller);
	bool TakeDamage(int amount, FString source) override;
	void Heal(int amount) override;
	void AdjustMaxHealth(int amount) override;
	void AdjustWalkSpeed(float percent);
	bool HasMovementComponent() override
	{
		return true;
	}
	void Kill() override;
	void Respawn(bool isDead) override;
	void AddEffect(UEffectData* effect) override;
	void CastSpell();
	void ChangeSpell(int slot);
	void ToggleSeek();
	virtual void CycleSpell();

	//---- HELPERS ----
	UCameraComponent* GetCamera() const noexcept;
	float GetHorizontalSensitivity() const noexcept;
	float GetVerticalSensitivity() const noexcept;
	IDamageable* GetDamageableAccess() override;
	IHealth* GetHealthAccess() override;
	AActor* GetSpellOwner() noexcept override;
	const FVector GetSpellOwnerLocation() noexcept override;
	const FVector GetSpellOwnerForward() noexcept override;
	const FVector GetCastStartLocation() noexcept override;
	const FVector GetCastStartForward() noexcept override;
	const int GetHealth(bool getPercent) noexcept override;
	const int GetMaxHealth() noexcept override;
	bool HasEffect(FString effectName) override;
	const FVector GetSeekLocation() const noexcept;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Test")
	TArray<TObjectPtr<USpellData>> spellData;
	UPROPERTY()
	TObjectPtr<USpellBase> spell;
	SpellType spellType;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float horizontalSensitivity;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float verticalSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UCameraComponent> camera;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> staticMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UHealthComponent> healthComponent;
	UPROPERTY()
	TObjectPtr<UEffectsComponent> effectComponent;

	UPROPERTY()
	TObjectPtr<AWWPlayerController> playerController;

	FVector spawnLocation;
	FVector lastValidPosition;
	float validUpdateTimer;

	float maxWalkSpeed;

	bool seek;

private:
	int _currentSpellIndex = 0;
};
