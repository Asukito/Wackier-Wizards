// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
#include "../../Interfaces/Effectable.h"
#include "../../Interfaces/Damageable.h"
#include "../../Interfaces/SpellCaster.h"
#include "../../Interfaces/Health.h"
#include "../../Spells/SpellType.h"
#include "VRCharacter.generated.h"

class UCameraComponent;
class AWWPlayerController;
class UStaticMeshComponent;
class UHealthComponent;
class USpellData;
class USpellBase;
class UEffectsComponent;

UCLASS()
class WACKIER_WIZARDS_API AVRCharacter : public ACharacter, public IEffectable, public IDamageable, public ISpellCaster, public IHealth
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

	// Input mapping context for VRCharacter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
	class UInputMappingContext* InputMappingContext;

	// Enhanced input subsystem for VRCharacter
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
	class UInputAction* inputMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
	class UInputAction* inputShootSpell;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
	class UInputAction* inputChangeSpell;

	void SetController(AWWPlayerController* controller);
	void TakeDamage(int amount, FString source) override;
	void Heal(int amount) override;
	void AdjustMaxHealth(int amount) override;
	void Kill() override;
	void Respawn() override;
	void AddEffect(UEffectData* effect) override;
	void CastSpell();
	void CycleSpell();
	void ChangeSpell(int slot);

	int currentSpellIndex = 0;

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
	const int GetHealth(bool getPercent) noexcept override;
	const int GetMaxHealth() noexcept override;
	bool HasEffect(FString effectName) override;
	const virtual FVector GetCastStartForward() noexcept override;



	//location of right hand to spawn spell
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Player Spell")
	FVector rightHandLocation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Function to shoot a spell
	UFUNCTION(BlueprintCallable, Category = "Player Spell")
	void ShootSpell();

	// Function to change the spell
	UFUNCTION(BlueprintCallable, Category = "Player Spell")
	void ChangeSpell();

	// Function to move the player character 
	UFUNCTION(BlueprintCallable, Category = "Player Movement")
	void MovePlayer(const FInputActionValue& Value);

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
	TObjectPtr<UEffectsComponent> _effectComponent;

	UPROPERTY()
	TObjectPtr<AWWPlayerController> _playerController;

	FVector _lastValidPosition;
	float _validUpdateTimer;
};
