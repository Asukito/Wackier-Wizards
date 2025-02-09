// Fill out your copyright notice in the Description page of Project Settings.


#include "VRCharacter.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"


// Sets default values
AVRCharacter::AVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	//Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	//Clear out the existing mappings, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	//Get the Enhanced Input Component
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// Bind the actions
	PEI->BindAction(inputMove, ETriggerEvent::Triggered, this, &AVRCharacter::MovePlayer);
	PEI->BindAction(inputShootSpell, ETriggerEvent::Triggered, this, &AVRCharacter::ShootSpell);
	PEI->BindAction(inputChangeSpell, ETriggerEvent::Triggered, this, &AVRCharacter::ChangeSpell);
}

void AVRCharacter::ShootSpell()
{
	//log that the player is shooting a spell
	UE_LOG(LogTemp, Warning, TEXT("Player is shooting a spell"));
}

void AVRCharacter::ChangeSpell()
{//log that the player is changing the spell
	UE_LOG(LogTemp, Warning, TEXT("Player is changing the spell"));
}

void AVRCharacter::MovePlayer(const FInputActionValue& Value)
{
	//log the value of the input action value
	
	UE_LOG(LogTemp, Warning, TEXT("Value: %s"), *Value.ToString());
	//checks if the player controller is valid
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		//gets the forward vector of the player controller
		FVector ForwardVector = PC->GetControlRotation().Vector();
		//gets the right vector of the player controller
		FVector RightVector = ForwardVector.RotateAngleAxis(90, FVector(0, 0, 1));
		//creates a movement vector
		FVector MovementVector = ForwardVector * Value.Get<FVector>().Y + RightVector * Value.Get<FVector>().X;
		//moves the player character
		AddMovementInput(MovementVector, 1);
		//prints the movement vector
		UE_LOG(LogTemp, Warning, TEXT("Movement Vector: %s"), *MovementVector.ToString());
	}

}

