// Fill out your copyright notice in the Description page of Project Settings.


#include "WWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.h"
#include "VRCharacter.h"
#include "../../Gamemodes/HubGameMode.h"
#include "../../GameInstance/UIManagerSubsystem.h"

#pragma region "Input Handlers"
void AWWPlayerController::UpdateSensitivity(float horizontal, float vertical)
{
	_horizontalSens = horizontal;
	_verticalSens = vertical;
}

void AWWPlayerController::HandleLook(const FInputActionValue& value)
{
	const FVector rotationVector = value.Get<FVector>();

	AddYawInput(rotationVector.X * _horizontalSens);
	AddPitchInput(rotationVector.Y * _verticalSens);
}

void AWWPlayerController::HandleMove(const FInputActionValue& value)
{
	const FVector movementVector = value.Get<FVector>();

	_playerCharacter->AddMovementInput(_playerCharacter->GetActorForwardVector(), movementVector.Y);
	_playerCharacter->AddMovementInput(_playerCharacter->GetCamera()->GetRightVector(), movementVector.X);
}

void AWWPlayerController::HandleJump()
{
	_playerCharacter->UnCrouch();
	_playerCharacter->Jump();
}
void AWWPlayerController::HandleCastSpell()
{
	_playerCharacter->CastSpell();
}
void AWWPlayerController::HandleDamageSelf()
{
	_playerCharacter->DealDamage(40, FString("Self"));
}
void AWWPlayerController::HandleSpellOne()
{
	_playerCharacter->ChangeSpell(1);
}
void AWWPlayerController::HandleSpellTwo()
{
	_playerCharacter->ChangeSpell(2);
}
void AWWPlayerController::HandleSpellThree()
{
	_playerCharacter->ChangeSpell(3);
}
void AWWPlayerController::HandleSpellFour()
{
	_playerCharacter->ChangeSpell(4);
}
void AWWPlayerController::HandleSpellFive()
{
	_playerCharacter->ChangeSpell(5);
}
void AWWPlayerController::HandleSpellSix()
{
	_playerCharacter->ChangeSpell(6);
}
void AWWPlayerController::HandleChangeSpell()
{
	_playerCharacter->CycleSpell();
}
void AWWPlayerController::HandleToggleSpellSelection()
{
	if (_uiManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller failed to initialise uiManager"));
		return;
	}

	if (Cast<AHubGameMode>(GetWorld()->GetAuthGameMode()) != nullptr)
	{
		_uiManager->ToggleWidget(EWidgetType::GRIMOIRE, this);
		return;
	}
}
void AWWPlayerController::HandleTogglePauseMenu()
{
	if (_uiManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller failed to initialise uiManager"));
		return;
	}

	_uiManager->ToggleWidget(EWidgetType::PAUSE_MENU, this);
}
#pragma endregion

void AWWPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (TObjectPtr<UUIManagerSubsystem> uiManager = GetGameInstance()->GetSubsystem<UUIManagerSubsystem>())
	{
		_uiManager = uiManager;
		_uiManager->CreateWidgets(this);
	}

	if (AVRCharacter* vr = Cast<AVRCharacter>(aPawn))
	{
		_playerCharacter = vr;
		_isVR = true;
	}
	else
	{
		_playerCharacter = Cast<APlayerCharacter>(aPawn);
	}

	_playerCharacter->SetController(this);
	_horizontalSens = _playerCharacter->GetHorizontalSensitivity();
	_verticalSens = _playerCharacter->GetVerticalSensitivity();
	_movementComponent = _playerCharacter->GetCharacterMovement();

	_enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(_enhancedInputComponent, TEXT("ENHANCED_INPUT_COMPONENT is an invalid value"));

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("INPUT_SUBSYSTEM is an invalid value"));

	//If the VRCharacter is used, bind VR input mappings.
	if (_isVR == true)
	{
		checkf(VR_inputMappingContext, TEXT("VR INPUT_MAPPING_CONTEXT is an invalid value"));
		inputSubsystem->ClearAllMappings();
		inputSubsystem->AddMappingContext(VR_inputMappingContext, 0);

		BindVRActions(_enhancedInputComponent);
	}
	else
	{
		checkf(inputMappingContext, TEXT("INPUT_MAPPING_CONTEXT is an invalid value"));
		inputSubsystem->ClearAllMappings();
		inputSubsystem->AddMappingContext(inputMappingContext, 0);

		BindActions(_enhancedInputComponent);
	}
}

void AWWPlayerController::OnUnPossess()
{
	_enhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void AWWPlayerController::BindActions(UEnhancedInputComponent* inputComponent)
{
	checkf(actionLook, TEXT("Missing 'Look' Action"));
	inputComponent->BindAction(actionLook, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleLook);

	checkf(actionMove, TEXT("Missing 'Move' Action"));
	inputComponent->BindAction(actionMove, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleMove);

	checkf(actionJump, TEXT("Missing 'Jump' Action"));
	inputComponent->BindAction(actionJump, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleJump);

	checkf(actionTest, TEXT("Missing 'Test' Action"));
	inputComponent->BindAction(actionTest, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleCastSpell);

	checkf(actionDamageSelf, TEXT("Missing 'DamageSelf' Action"));
	inputComponent->BindAction(actionDamageSelf, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleDamageSelf);

	checkf(actionSpellOne , TEXT("Missing 'SpellOne' Action"));
	inputComponent->BindAction(actionSpellOne, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleSpellOne);

	checkf(actionSpellTwo, TEXT("Missing 'SpellTwo' Action"));
	inputComponent->BindAction(actionSpellTwo, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleSpellTwo);

	checkf(actionSpellThree, TEXT("Missing 'SpellThree' Action"));
	inputComponent->BindAction(actionSpellThree, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleSpellThree);

	checkf(actionSpellFour, TEXT("Missing 'SpellFour' Action"));
	inputComponent->BindAction(actionSpellFour, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleSpellFour);

	checkf(actionSpellFive, TEXT("Missing 'SpellFive' Action"));
	inputComponent->BindAction(actionSpellFive, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleSpellFive);

	checkf(actionSpellSix, TEXT("Missing 'SpellSix' Action"));
	inputComponent->BindAction(actionSpellSix, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleSpellSix);

	checkf(actionToggleSpellSelection, TEXT("Missing 'ToggleSpellSelection' Action"));
	inputComponent->BindAction(actionToggleSpellSelection, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleToggleSpellSelection);

	checkf(actionTogglePauseMenu, TEXT("Missing 'TogglePauseMenu' Action"));
	inputComponent->BindAction(actionTogglePauseMenu, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleTogglePauseMenu);
}

void AWWPlayerController::BindVRActions(UEnhancedInputComponent* inputComponent)
{
	checkf(VR_actionMove, TEXT("Missing 'Move' Action"));
	inputComponent->BindAction(VR_actionMove, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleMove);

	checkf(VR_actionCastSpell, TEXT("Missing 'Move' Action"));
	inputComponent->BindAction(VR_actionCastSpell, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleCastSpell);

	checkf(VR_actionChangeSpell, TEXT("Missing 'Move' Action"));
	inputComponent->BindAction(VR_actionChangeSpell, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleChangeSpell);
}
