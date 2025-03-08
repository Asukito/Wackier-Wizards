// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"

class UInputMappingContext;
class UEnhancedInputComponent;
class UInputAction;
class UCharacterMovementComponent;
class APlayerCharacter;
class UUIManagerSubsystem;

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
	void HandleCastSpell();
	void HandleDamageSelf();
	void HandleSpellOne();
	void HandleSpellTwo();
	void HandleSpellThree();
	void HandleSpellFour();
	void HandleSpellFive();
	void HandleSpellSix();
	void HandleChangeSpell();
	void HandleToggleSpellSelection();
	void HandleTogglePauseMenu();

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
private:
	void BindActions(UEnhancedInputComponent* inputComponent);
	void BindVRActions(UEnhancedInputComponent* inputComponent);

public:
	//---- INPUTS ----
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | VR | Mapping Context")
	TObjectPtr<UInputMappingContext> VR_inputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | VR | Character Movement")
	TObjectPtr<UInputAction> VR_actionMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | VR | Character Actions")
	TObjectPtr<UInputAction> VR_actionCastSpell;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | VR | Character Actions")
	TObjectPtr<UInputAction> VR_actionChangeSpell;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Mapping Context")
	TObjectPtr<UInputMappingContext> inputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Movement")
	TObjectPtr<UInputAction> actionLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Movement")
	TObjectPtr<UInputAction> actionMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Movement")
	TObjectPtr<UInputAction> actionJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionTest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionDamageSelf;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionSpellOne;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionSpellTwo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionSpellThree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionSpellFour;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionSpellFive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionSpellSix;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionChangeSpell;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionToggleSpellSelection;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input | Keyboard/Mouse | Character Actions")
	TObjectPtr<UInputAction> actionTogglePauseMenu;
private:
	UPROPERTY()
	TObjectPtr<UUIManagerSubsystem> _uiManager;
	UPROPERTY()
	TObjectPtr<UEnhancedInputComponent> _enhancedInputComponent;

	TWeakObjectPtr<APlayerCharacter> _playerCharacter;
	TWeakObjectPtr<UCharacterMovementComponent> _movementComponent;

	float _horizontalSens;
	float _verticalSens;

	bool _isVR;
};
