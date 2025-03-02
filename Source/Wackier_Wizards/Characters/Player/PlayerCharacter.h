// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class AWWPlayerController;
class USpellCasterComponent;

UCLASS()
class WACKIER_WIZARDS_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

//Base PlayerCharacter class. BaseCharacter with additional SpellCaster component as well as player-unique logic. 
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	//---- IHEALTH OVERRIDES ----
	void Respawn(bool isDead) override;

	//---- SPELL FUNCTIONS ----
	void CastSpell();
	UFUNCTION(BlueprintCallable)
	void ChangeSpell(int slot);
	virtual void CycleSpell();
	UFUNCTION(BlueprintCallable)
	void InitSpells();

	//---- HELPERS ----
	UCameraComponent* GetCamera() const noexcept;
	float GetHorizontalSensitivity() const noexcept;
	float GetVerticalSensitivity() const noexcept;
	virtual const FVector GetCastStartLocation();
	virtual const FVector GetCastStartForward();
	void SetController(AWWPlayerController* controller);

	//---- TEST ----
	//Test function for Toggling AI seeking. Currently not in use and doesn't affect anything. 
	void ToggleSeek();
	//Returns the actor location if seeking is active. Returns a zero vector if not. Currently not used.
	const FVector GetSeekLocation() const noexcept;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void BindDelegates() override;
protected:
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float horizontalSensitivity;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float verticalSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UCameraComponent> camera;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USpellCasterComponent> spellCasterComponent;

	UPROPERTY()
	TObjectPtr<AWWPlayerController> playerController;

	FVector lastValidPosition;
	float validUpdateTimer;

	bool seek;
};
