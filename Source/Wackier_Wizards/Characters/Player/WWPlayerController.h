// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class UInputAction;
class UCharacterMovementComponent;
class AVRCharacter;

UCLASS()
class WACKIER_WIZARDS_API AWWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void UpdateSensitivity(float horizontal, float vertical);

protected:
	//---- INPUT HANDLERS ----
	void HandleLook(const struct FInputActionValue& value);
	void HandleMove(const struct FInputActionValue& value);
	void HandleJump();
	void HandleTest();
	void HandleDamageSelf();
	void HandleSpellOne();
	void HandleSpellTwo();
	void HandleSpellThree();
	void HandleSpellFour();
	void HandleSpellFive();
	void HandleSpellSix();
	void HandleChangeSpell();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
private:
	void BindActions(UEnhancedInputComponent* inputComponent);

public:
	//---- INPUTS ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Mapping Context")
	TObjectPtr<UInputMappingContext> inputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputAction> actionLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputAction> actionMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Movement")
	TObjectPtr<UInputAction> actionJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionTest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionDamageSelf;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionSpellOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionSpellTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionSpellThree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionSpellFour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionSpellFive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionSpellSix;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Character Actions")
	TObjectPtr<UInputAction> actionChangeSpell;
private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> _enhancedInputComponent;

	TWeakObjectPtr<AVRCharacter> _playerCharacter;
	TWeakObjectPtr<UCharacterMovementComponent> _movementComponent;

	float _horizontalSens;
	float _verticalSens;
};
