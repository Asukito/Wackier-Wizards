// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

UCLASS()
class WACKIER_WIZARDS_API APlayerCharacter : public ACharacter, public IDamageable, public ISpellCaster, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void SetController(AWWPlayerController* controller);
	void TakeDamage(int amount, FString source) override;
	void Heal(int amount) override;
	void Kill() override;
	void Respawn() override;
	void CastSpell();
	void ChangeSpell(int slot);

	//---- HELPERS ----
	UCameraComponent* GetCamera() const noexcept;
	float GetHorizontalSensitivity() const noexcept;
	float GetVerticalSensitivity() const noexcept;
	AActor* GetSpellOwner() noexcept override;
	const FVector GetSpellOwnerLocation() noexcept override;
	const FVector GetSpellOwnerForward() noexcept override;
	const FVector GetCastStartLocation() noexcept override;
	const int GetHealth(bool getPercent) noexcept override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Test")
	TArray<TObjectPtr<USpellData>> spellData;
	UPROPERTY()
	TObjectPtr<USpellBase> spell;
	SpellType spellType;

	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float _horizontalSensitivity;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float _verticalSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UCameraComponent> _camera;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> _staticMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UHealthComponent> _healthComponent;

	TWeakObjectPtr<AWWPlayerController> _playerController;

	FVector _lastValidPosition;
	float _validUpdateTimer;
};
