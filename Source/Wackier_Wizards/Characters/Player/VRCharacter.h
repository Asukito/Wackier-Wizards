// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedPlayerInput.h"
#include "VRCharacter.generated.h"


UCLASS()
class WACKIER_WIZARDS_API AVRCharacter : public ACharacter
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

};
