// Fill out your copyright notice in the Description page of Project Settings.


#include "WWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "PlayerCharacter.h"

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
void AWWPlayerController::HandleTest()
{
	_playerCharacter->CastSpell();
}
void AWWPlayerController::HandleDamageSelf()
{
	_playerCharacter->TakeDamage(40, FString("Self"));
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
void AWWPlayerController::HandleToggleSeek()
{
	_playerCharacter->ToggleSeek();
}
#pragma endregion

void AWWPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	_playerCharacter = Cast<APlayerCharacter>(aPawn);
	_playerCharacter->SetController(this);
	_horizontalSens = _playerCharacter->GetHorizontalSensitivity();
	_verticalSens = _playerCharacter->GetVerticalSensitivity();
	_movementComponent = _playerCharacter->GetCharacterMovement();

	_enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(_enhancedInputComponent, TEXT("ENHANCED_INPUT_COMPONENT is an invalid value"));

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(inputSubsystem, TEXT("INPUT_SUBSYSTEM is an invalid value"));

	checkf(inputMappingContext, TEXT("INPUT_MAPPING_CONTEXT is an invalid value"));
	inputSubsystem->ClearAllMappings();
	inputSubsystem->AddMappingContext(inputMappingContext, 0);

	BindActions(_enhancedInputComponent);
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
	inputComponent->BindAction(actionTest, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleTest);

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

	checkf(actionToggleSeek, TEXT("Missing 'ToggleSeek' Action"));
	inputComponent->BindAction(actionToggleSeek, ETriggerEvent::Triggered, this, &AWWPlayerController::HandleToggleSeek);
}
