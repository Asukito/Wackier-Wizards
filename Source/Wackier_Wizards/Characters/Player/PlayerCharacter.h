// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SpellCasterCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class AWWPlayerController;

UCLASS()
class WACKIER_WIZARDS_API APlayerCharacter : public ASpellCasterCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	void SetController(AWWPlayerController* controller);
	void ToggleSeek();
	void Respawn(bool isDead) override;

	//---- HELPERS ----
	UCameraComponent* GetCamera() const noexcept;
	float GetHorizontalSensitivity() const noexcept;
	float GetVerticalSensitivity() const noexcept;
	const FVector GetSpellOwnerForward() noexcept override;
	const FVector GetCastStartLocation() noexcept override;
	const FVector GetCastStartForward() noexcept override;
	const FVector GetSeekLocation() const noexcept;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float horizontalSensitivity;
	UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0.01", ClampMax = "1.0"))
	float verticalSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<UCameraComponent> camera;

	UPROPERTY()
	TObjectPtr<AWWPlayerController> playerController;

	FVector lastValidPosition;
	float validUpdateTimer;

	bool seek;
};
